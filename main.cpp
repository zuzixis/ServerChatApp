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
#include "Cryptograph.h"
#include <regex>

#define MAX_CLIENTS 100
#define BUFFER_SZ 4096

using json = nlohmann::json;
static unsigned int cli_count = 0;
static int uid = 10;


pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
//ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();


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
    char buffer[BUFFER_SZ];
    int receiveSendStatus;
//    bool enableNavigation;
    string output;
    User *user = nullptr;

//    int keepalive = 5;
//    int keepcount = 3;
//
//    setsockopt(rs, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepalive , sizeof(keepalive ));
//    setsockopt(rs, SOL_TCP, TCP_KEEPIDLE, (void*)&keepidle , sizeof(keepidle ));
//    setsockopt(rs, SOL_TCP, TCP_KEEPINTVL, (void *)&keepinterval , sizeof(keepinterval ));
//    setsockopt(rs, SOL_TCP, TCP_KEEPCNT, (void *)&keepcount , sizeof(keepcount ));
    string final;
    while (1) {


//        final = "";
        bzero(buffer, BUFFER_SZ);
        receiveSendStatus = recv(connfd, buffer, BUFFER_SZ, 0);
//        do {
//
//            final += buffer;
//        } while (receiveSendStatus > 0);
//        receive = recv(connfd, buffer, BUFFER_SZ, 0);
        if (receiveSendStatus > 0) {
//            cout << "buffer: " << buffer << endl;
            string inp = Cryptograph::decrypt(buffer);
            json j = json::parse(inp);
            bzero(buffer, BUFFER_SZ);
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
                        /* Add client to the queue and fork thread */
                        user = ActiveUsersProvider::getInstance().getLastUser();

                        output = R"({"status": 200,"data":{"id":)" + returnFromRedirect + "}}";

//                        output = R"({"status":200,"data":{}})";
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
            output = Cryptograph::encrypt(output);
            cout << "output" << output <<  endl;
            Helpers::sgets(buffer, BUFFER_SZ, &output);
            receiveSendStatus = send(connfd, buffer, strlen(buffer), 0);
//            do {
////                final += buffer;
//            } while (receiveSendStatus > 0);
        } else if (receiveSendStatus < 0) {
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
//    queue_remove(cli->uid);
//    free(cli);
    cli_count--;

//    pthread_detach(pthread_self());

    return NULL;
}

int main(int argc, char **argv) {

//    MessageController m;
//    m.getConversation(nullptr);

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

    printf("=== Vitaj na Bajsfuku ===\n");

    while (1) {
        socklen_t clilen = sizeof(cli_addr);
        connfd = accept(listenfd, (struct sockaddr *) &cli_addr, &clilen);

        // TODO: tu daj login a registraciu z vlakna

        /* Check if max clients is reached */
        if ((ActiveUsersProvider::getInstance().getActiveUsers()->size() + 1) == MAX_CLIENTS) {
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