#pragma once

#include <iostream>
#include <string>
#include <map>

#include "controllers/AuthController.h"
#include "controllers/ContactsController.h"
#include "controllers/GroupsController.h"
#include "controllers/MessageController.h"
#include "providers/ActiveUsersProvider.h"

using namespace std;

class Navigator {
private:
    int *connfd;
//    int newUid;
//    sockaddr_in *cliAddr;
    AuthController *authController;
    ContactsController *contactsController;
    GroupsController *groupsController;
    MessageController *messageController;
    ActiveUsersProvider *activeUsersProvider;

public:
    Navigator(int* connfd) {
        this->connfd = connfd;
//        this->newUid = newUid;
//        this->cliAddr = cliAddr;
        activeUsersProvider = new ActiveUsersProvider();
        authController = new AuthController(activeUsersProvider);
        contactsController = new ContactsController();
        groupsController = new GroupsController();
        messageController = new MessageController();
    }

    ~Navigator() {
        delete authController;
        delete contactsController;
        delete groupsController;
        delete messageController;
        delete activeUsersProvider;
    }

    map<string, string> redirect(const string &action, map<string, string> &data);
};

