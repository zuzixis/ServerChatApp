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
    AuthController* authController;
    ContactsController* contactsController;
    GroupsController* groupsController;
    MessageController* messageController;

public:
    Navigator(){
        authController = new AuthController();
        contactsController = new ContactsController();
        groupsController  = new GroupsController();
        messageController = new MessageController();
    }
    ~Navigator(){
        delete authController;
        delete contactsController;
        delete groupsController;
        delete messageController;
    }


    bool redirect(string action, map<string,string>* data){

        if (action.compare("LOGIN") == 0){
            //
        }else if (action.compare("LOGOUT")){
            //
        }else if (action.compare("DELETE_ACCOUNT")){
            //
        }else if (action.compare("REGISTER")){
            //
        }else if (action.compare("GET_CONTACTS")){
            //
        }else if (action.compare("GET_GROUPS")){
            //
        }else if (action.compare("GET_CONVERSATION")){
            //
        }else if (action.compare("ASK_FOR_REQUESTS_CONTACT")){
            //
        }else if (action.compare("GET_CONTACT_REQUESTS")){

        }else if (action.compare("CONFIRMATION_CONTACT_REQUEST")){

        }else if (action.compare("SEND_MESSAGE")){
            //
        }else if (action.compare("SEND_FILE")){
            //
        }else if (action.compare("SEND_IMAGE")){
            //
        }

    }


};

