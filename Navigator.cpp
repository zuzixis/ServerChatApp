//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "Navigator.h"

string Navigator::redirect(const string &action, json &data) {

    if (action == "LOGIN") {
//        map<string, string> map = {{"name", "jozo"}, {"password", "pass"}};
        return this->authController->login(&data,this->connfd);
    } else if (action == "LOGOUT") {
       // return this->authController->logout(&data,this->connfd);
    } else if (action == "DELETE_ACCOUNT") {
        //
    } else if (action == "REGISTER") {
        //authController->createAccount(&data);
    } else if (action == "GET_CONTACTS") {
        //
    } else if (action == "GET_GROUPS") {
        //
    } else if (action == "GET_CONVERSATION") {
        //
    } else if (action == "ASK_FOR_REQUESTS_CONTACT") {
        //
    } else if (action == "GET_CONTACT_REQUESTS") {

    } else if (action == "CONFIRMATION_CONTACT_REQUEST") {

    } else if (action == "SEND_MESSAGE") {
        //
    } else if (action == "SEND_FILE") {
        //
    } else if (action == "SEND_IMAGE") {
        //
    }

    return {};
}