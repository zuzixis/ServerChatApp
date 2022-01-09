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
#include <assert.h>
#include <sys/types.h>
#include <signal.h>
#include <poll.h>
#include "providers/ActiveUsersProvider.h"
#include "Navigator.h"
#include "Helpers.h"
#include <string.h>
#include "Cryptograph.h"
#include <regex>

#define MAX_CLIENTS 100
#define BUFFER_SZ 1024

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


    int receivedSize;
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
    while (1) {
        bzero(buffer, BUFFER_SZ);

        string final = "";
//        final = "";
        string msgSizeString;

        struct pollfd pfd;
        pfd.fd = connfd;
        pfd.events = POLLIN | POLLHUP | POLLRDNORM;
        pfd.revents = 0;
//        bool clientClosed = false;
//        while (pfd.revents == 0) {
//            // call poll with a timeout of 100 ms
//            if (poll(&pfd, 1, 100) > 0) {
//                // if result > 0, this means that there is either data available on the
//                // socket, or the socket has been closed
////                char buffer[32];
//                if (recv(connfd, buffer, BUFFER_SZ-1, MSG_PEEK | MSG_DONTWAIT) == 0) {
//                    // if recv returns zero, that means the connection has been closed:
//                    clientClosed = true;
//
//                }
//            }
//        }

        //bzero(buffer, BUFFER_SZ);
        receivedSize = recv(connfd, buffer, BUFFER_SZ-1, 0);
        final = buffer;

//        int msgSize = 0;
//        while (!clientClosed && (msgSize == 0 || msgSize > final.size())) {
//        bzero(buffer, BUFFER_SZ);
//            receivedSize = recv(connfd, buffer, BUFFER_SZ-1, 0);
//            if (receivedSize > 0){
//                if ( msgSize == 0) {
//                    final = buffer;
//                    assert(final.find('|') != string::npos);
//
//                    size_t msgSizeLength = final.find('|');
//                    msgSizeString = final.substr(0, msgSizeLength);
//                    if (Helpers::isNumber(msgSizeString)) {
//                        msgSize = stoi(msgSizeString);
//                        final = final.substr(msgSizeLength + 1);
//                    }
//                } else {
//                    final += buffer;
//                }
//            }
//
//
//            bzero(buffer, BUFFER_SZ);
//        }
//        bzero(buffer, BUFFER_SZ);

//        if ( clientClosed || receivedSize < 0) {
//            break;
//        }

        if (!final.empty()) {
//            cout << "buffer: " << buffer << endl;
//            string inp = final;
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
            cout << "output" << output << endl;
            output = Cryptograph::encrypt(output);
            //output = to_string(output.size())+'|'+output;
//            Helpers::sgets(buffer, BUFFER_SZ, &output);




            receivedSize = send(connfd, output.c_str(), strlen(output.c_str()), 0);
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
        if ((ActiveUsersProvider::getInstance().getActiveUsers().size() + 1) == MAX_CLIENTS) {
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