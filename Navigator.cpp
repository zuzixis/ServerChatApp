//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "Navigator.h"

string Navigator::redirect(const string &action, json &data) {


    if (action == "LOGIN") {
//        map<string, string> map = {{"name", "jozo"}, {"password", "pass"}};
        return this->authController->login(&data, this->connfd);
    } else if (action == "REGISTER") {
        return this->authController->createAccount(&data);
    }
//    else if (action == "LOGOUT") {
//        return this->authController->logout(&data);
//    }
    if (ActiveUsersProvider::getInstance().getActualUserId() > 0) {
        if (action == "DELETE_ACCOUNT") {
            return this->authController->deleteAccount(&data);
        } else if (action == "GET_CONTACTS") {
            return this->contactsController->getContacts(&data);
        } else if (action == "GET_GROUPS") {
            return this->groupsController->getGroups(&data);
        } else if (action == "GET_CONVERSATION") {
            return this->messageController->getConversation(&data);
        } else if (action == "ASK_FOR_REQUESTS_CONTACT") {
            return this->requestsController->askForRequestsContact(&data);
        } else if (action == "GET_CONTACT_REQUESTS") {
            return this->requestsController->getContactRequests(&data);
        } else if (action == "CONFIRMATION_CONTACT_REQUEST") {
            return this->requestsController->confirmationContactRequest(&data);
        } else if (action == "REJECT_CONTACT_REQUEST") {
            return this->requestsController->rejectContactRequest(&data);
        } else if (action == "SEND_MESSAGE") {
            return this->messageController->sendMessage(&data);
        } else if (action == "SEARCH_USERS") {
            return this->userController->search(&data);
        } else if (action == "SEARCH_GROUPS") {
            return this->groupsController->search(&data);
        } else if (action == "CREATE_GROUP") {
            return this->groupsController->create(&data);
        } else if (action == "REMOVE_FROM_CONTACTS") {
            return this->contactsController->removeFromContacts(&data);
        }  else if (action == "JOIN_TO_GROUP") {
            return this->groupsController->joinToGroup(&data);
        }else if (action == "REMOVE_GROUP") {
            return this->groupsController->removeGroup(&data);
        }else if (action == "UNJOIN_FROM_GROUP") {
            return this->groupsController->unjoinFromGroup(&data);
        }else if (action == "GET_MESSAGE_BY_ID") {
            return this->messageController->getMessageById(&data);
        }
    }


    return R"({"status": 405,"data":{"msg":"Zlá adresa."}})";
}