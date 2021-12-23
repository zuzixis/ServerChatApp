#include "AuthController.h"
AuthController::AuthController() {

}

AuthController::~AuthController() {

}


map<string, string> AuthController::login(const map<string, string> *data) {
    return map<string, string>();
}

bool AuthController::logout(const map<string, string> *data) {
    return false;
}

bool AuthController::deleteAccount(const map<string, string> *data) {
    return false;
}

bool AuthController::createAccount(const map<string, string> *data) {
    return false;
}