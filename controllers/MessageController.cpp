//
// Created by Zuzana Žillová on 23. 12. 2021.
//

#include "MessageController.h"

MessageController::MessageController() {

}

MessageController::~MessageController() {

}

bool MessageController::sendMessage(const map<string, string> *data) {
    return false;
}

bool MessageController::sendFile(const map<string, string> *data) {
    return false;
}

bool MessageController::sendImage(const map<string, string> *data) {
    return false;
}

map<string, string> MessageController::getConversation(const map<string, string> *data) {
    return map<string, string>();
}
