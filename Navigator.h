#pragma once

#include <iostream>
#include <string>
#include <map>

#include "controllers/AuthController.h"
#include "controllers/ContactsController.h"
#include "controllers/GroupsController.h"
#include "controllers/MessageController.h"

using namespace std;

class Navigator {
private:
    AuthController *authController;
    ContactsController *contactsController;
    GroupsController *groupsController;
    MessageController *messageController;

public:
    Navigator() {
        authController = new AuthController();
        contactsController = new ContactsController();
        groupsController = new GroupsController();
        messageController = new MessageController();
    }

    ~Navigator() {
        delete authController;
        delete contactsController;
        delete groupsController;
        delete messageController;
    }

    map<string, string> redirect(const string &action, map<string, string> &data);
};

