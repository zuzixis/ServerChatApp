//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "MessageController.h"
#include "../providers/ActiveUsersProvider.h"

MessageController::MessageController() {

}

MessageController::~MessageController() {

}

bool MessageController::sendMessage(const map<string, string> *data) {
    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
    vector<User *> acceptorConnections = activeUsersProvider.getById(stoi(data->at("to")));
    // TODO: activeUsersProvider sa moze skor vola ActiveConnectionsProvider a tam by bol user a fd
    for (auto &userConnection: acceptorConnections) // access by reference to avoid copying
    {
        send(userConnection->getSockfd(), "", 10, 0);
    }
// TODO: user nemusi byt prihlaseny, teda musim si danu spravu ulozit do suboru a aj do premennej.
//  V subore budu vsetky spravy aj s priznakom, ci uz boli precitane
}

bool MessageController::sendFile(const map<string, string> *data) {
    return false;
}

bool MessageController::sendImage(const map<string, string> *data) {
    return false;
}

map<string, string> MessageController::getConversation(const map<string, string> *data) {
//    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
// TODO: ideme davat do usera spravy?

//    return user->getMessages();
    return map<string, string>();
}
