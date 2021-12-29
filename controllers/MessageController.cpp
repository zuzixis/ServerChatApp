//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "MessageController.h"

MessageController::MessageController() {

}

MessageController::~MessageController() {

}

string MessageController::sendMessage(const json *data) {
//    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
//    vector<User *> acceptorConnections = activeUsersProvider.getById(stoi(data->at("to")));
//    // TODO: activeUsersProvider sa moze skor vola ActiveConnectionsProvider a tam by bol user a fd
//    for (auto &userConnection: acceptorConnections) // access by reference to avoid copying
//    {
//        send(userConnection->getSockfd(), "", 10, 0);
//    }
return "";
// TODO: user nemusi byt prihlaseny, teda musim si danu spravu ulozit do suboru a aj do premennej.
//  V subore budu vsetky spravy aj s priznakom, ci uz boli precitane
}

string MessageController::sendFile(const json *data) {
    return "false";
}

string MessageController::sendImage(const json *data) {
    return "false";
}

string MessageController::getConversation(const json *data) {
//    ActiveUsersProvider activeUsersProvider = ActiveUsersProvider::getInstance();
// TODO: ideme davat do usera spravy?

//    return user->getMessages();
    return "map<string, string>()";
}
