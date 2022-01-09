#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <signal.h>
#include "providers/ActiveUsersProvider.h"
#include "Navigator.h"
#include "Helpers.h"
#include "Cryptograph.h"

#define MAX_CLIENTS 100
#define BUFFER_SZ 1024

using json = nlohmann::json;

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void print_client_addr(struct sockaddr_in addr) {
    printf("%d.%d.%d.%d",
           addr.sin_addr.s_addr & 0xff,
           (addr.sin_addr.s_addr & 0xff00) >> 8,
           (addr.sin_addr.s_addr & 0xff0000) >> 16,
           (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

/* Handle all communication with the client */
// TODO: Z tohto vlakna dame do mainu login a registraciu
void *handle_client(int connfd) {

    char buffer[BUFFER_SZ];

    int receivedSize;
    string output;
    User *user = nullptr;

    while (true) {
        bzero(buffer, BUFFER_SZ);

        string final;
        string msgSizeString;

        receivedSize = recv(connfd, buffer, BUFFER_SZ - 1, 0);
        final = buffer;

        if (!final.empty()) {
            string inp = Cryptograph::decrypt(final);
            json j = json::parse(inp);
            cout << j << endl;
            if (j.contains("data") && j.contains("action")) {

                if (j["action"] == "LOGIN" || j["action"] == "REGISTER" || user != nullptr) {
                    pthread_mutex_lock(&clients_mutex);
                    if (user != nullptr) {
                        ActiveUsersProvider::getInstance().setActualUserId(user->getId());
                    } else {
                        ActiveUsersProvider::getInstance().setActualUserId(0);
                    }

                    Navigator n(&connfd);
                    string returnFromRedirect = n.redirect(j["action"], j["data"]);
                    pthread_mutex_unlock(&clients_mutex);

                    if (j["action"] == "LOGIN" && Helpers::isNumber(returnFromRedirect)) {
                        // vratilo sa id usera
                        user = ActiveUsersProvider::getInstance().getLastUser();

                        output = R"({"status": 200,"data":{"id":)" + returnFromRedirect + "}}";

                    } else if (j["action"] == "LOGOUT" ||
                               (j["action"] == "REGISTER" && returnFromRedirect == R"({"status": 200,"data":{}})")) {
                        pthread_mutex_lock(&clients_mutex);
                        ActiveUsersProvider::getInstance().removeUser(user);
                        user = nullptr;
                        pthread_mutex_unlock(&clients_mutex);
                        output = R"({"status":200,"data":{}})";
                    } else {
                        output = returnFromRedirect;
                    }
                } else {
                    output = R"({"status":403,"data":{"msg":"Pre danu akciu musite byt prihlaseny"}})";// TODO: do dat daj, v com bola chyba
                }
            } else {
                //vrati sa chyba, že data nie su kompletne
                output = R"({"status":422,"data":{"msg":""}})";// TODO: do dat daj, v com bola chyba
            }
            cout << "output" << output << endl;
            output = Cryptograph::encrypt(output);
            output = to_string(output.size())+'|'+output;

            receivedSize = send(connfd, output.c_str(), strlen(output.c_str()), 0);
        }
        if (receivedSize < 0) {
            break;
        }
    }

    /* Delete client from queue and yield thread */
    close(connfd);
    if (user) {
        pthread_mutex_lock(&clients_mutex);
        ActiveUsersProvider::getInstance().removeUser(user);
        pthread_mutex_unlock(&clients_mutex);
    }
    cout << "Koncim vlakno" << endl;

    return NULL;
}

int main(int argc, char **argv) {


    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    string ip = Helpers::IP;

    int port = atoi(argv[1]);
    int option = 1;
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int optval;
    socklen_t optlen = sizeof(optval);

    /* Socket settings */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    serv_addr.sin_port = htons(port);

    /* Ignore pipe signals */
    signal(SIGPIPE, SIG_IGN);

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char *) &option, sizeof(option)) < 0) {
        perror("ERROR: setsockopt failed");
        return EXIT_FAILURE;
    }

    /* Set the option active */
    optval = 500;
    optlen = sizeof(optval);
    if (setsockopt(listenfd, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
        perror("setsockopt()");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    /* Bind */
    if (::bind(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR: Socket binding failed");
        return EXIT_FAILURE;
    }

    /* Listen */
    if (listen(listenfd, 10) < 0) {
        perror("ERROR: Socket listening failed");
        return EXIT_FAILURE;
    }

    printf("=== Vitaj na serveri ===\n");

    while (true) {
        socklen_t clilen = sizeof(cli_addr);
        connfd = accept(listenfd, (struct sockaddr *) &cli_addr, &clilen);

        // TODO: tu daj login a registraciu z vlakna

        /* Check if max clients is reached */
        pthread_mutex_lock(&clients_mutex);
        if ((ActiveUsersProvider::getInstance().getActiveUsers().size()) == MAX_CLIENTS) {
            printf("Max clients reached. Rejected: ");
            print_client_addr(cli_addr);
            printf(":%d\n", cli_addr.sin_port);
            close(connfd);
            continue;
        }
        pthread_mutex_unlock(&clients_mutex);

        thread tid(handle_client, connfd);
        tid.detach();

        /* Reduce CPU usage */
        sleep(1);
    }
}