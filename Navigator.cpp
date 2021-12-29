//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "Navigator.h"

string Navigator::redirect(const string &action, json &data) {

    if (action == "LOGIN") {
//        map<string, string> map = {{"name", "jozo"}, {"password", "pass"}};
        return this->authController->login(&data,this->connfd);
    } else if (action == "LOGOUT") {
        return this->authController->logout(&data);
    } else if (action == "DELETE_ACCOUNT") {
        return this->authController->deleteAccount(&data);
    } else if (action == "REGISTER") {
        return this->authController->createAccount(&data);
    } else if (action == "GET_CONTACTS") {
        //
    } else if (action == "GET_GROUPS") {
        //
    } else if (action == "GET_CONVERSATION") {
        messageController->getConversation(&data);
    } else if (action == "ASK_FOR_REQUESTS_CONTACT") {
        //
    } else if (action == "GET_CONTACT_REQUESTS") {

    } else if (action == "CONFIRMATION_CONTACT_REQUEST") {

    } else if (action == "SEND_MESSAGE") {
        messageController->sendMessage(&data);
    } else if (action == "SEND_FILE") {
        messageController->sendFile(&data);
    } else if (action == "SEND_IMAGE") {
        messageController->sendImage(&data);
    }

    return "false";
}