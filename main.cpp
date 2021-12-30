#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <sys/types.h>
#include <signal.h>
#include "providers/ActiveUsersProvider.h"
#include "Navigator.h"
#include "Helpers.h"
#include <string.h>
#include <regex>

#define MAX_CLIENTS 100
#define BUFFER_SZ 2048

using json = nlohmann::json;
static unsigned int cli_count = 0;
static int uid = 10;


pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();


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
    char buff_out[BUFFER_SZ];
    char name[32];

    cli_count++;

    sprintf(buff_out, "Someone has joined\n");

    bzero(buff_out, BUFFER_SZ);
    char buffer[256];
    int receive;
//    bool enableNavigation;
    string output;
    User *user;

    while (1) {

        bzero(buffer, BUFFER_SZ);
        receive = recv(connfd, buffer, BUFFER_SZ, 0);
        if (receive >= 0) {
            json j = json::parse(buffer);
            bzero(buffer, BUFFER_SZ);
            cout << j << endl;
            if (j.contains("data") && j.contains("action")) {

                if (j["action"] == "LOGIN" || j["action"] == "REGISTER" || user != nullptr) {
                    pthread_mutex_lock(&clients_mutex);
                    Navigator n(&connfd);
                    string returnFromRedirect = n.redirect(j["action"], j["data"]);
                    pthread_mutex_unlock(&clients_mutex);

                    if (j["action"] == "LOGIN" && Helpers::isNumber(returnFromRedirect)) {
                        // vratilo sa id usera
                        /* Add client to the queue and fork thread */
                        user = activeUsersProvider.getLastUser();
                        output = R"({"status":200,"data":{}})";
                    } else if (j["action"] == "LOGOUT") {
                        pthread_mutex_lock(&clients_mutex);
                        activeUsersProvider.removeUser(user);
                        pthread_mutex_unlock(&clients_mutex);
                        output = R"({"status":200,"data":{}})";
                    } else {
                        output = returnFromRedirect;
                    }
                } else {
                    output = R"({"status":403,"data":{}})";// TODO: do dat daj, v com bola chyba
                }
            } else {
                //vrati sa chyba, že data nie su kompletne
                output = R"({"status":422,"data":{}})";// TODO: do dat daj, v com bola chyba
            }
            Helpers::sgets(buffer, 255, &output);
            send(connfd, buffer, strlen(buffer), 0);
        } else {
            break;
        }
    }

    /* Delete client from queue and yield thread */
    close(connfd);
    if (user) {
        pthread_mutex_lock(&clients_mutex);
        activeUsersProvider.removeUser(user);
        pthread_mutex_unlock(&clients_mutex);
    }
    cout << "Koncim vlakno" << endl;
//    queue_remove(cli->uid);
//    free(cli);
    cli_count--;

//    pthread_detach(pthread_self());

    return NULL;
}

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    string ip = "127.0.0.1";
    int port = atoi(argv[1]);
    int option = 1;
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
//    thread();


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

    printf("=== Vitaj na Bajsfuku ===\n");

    while (1) {
        socklen_t clilen = sizeof(cli_addr);
        connfd = accept(listenfd, (struct sockaddr *) &cli_addr, &clilen);

        // TODO: tu daj login a registraciu z vlakna

        /* Check if max clients is reached */
        if ((activeUsersProvider.getActiveUsers()->size() + 1) == MAX_CLIENTS) {
            printf("Max clients reached. Rejected: ");
            print_client_addr(cli_addr);
            printf(":%d\n", cli_addr.sin_port);
            close(connfd);
            continue;
        }

        thread tid(handle_client, connfd);
        tid.detach();

        /* Reduce CPU usage */
        sleep(1);
    }
}