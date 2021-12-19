#include "iostream"
//
// Created by Zuzana Žillová on 19. 12. 2021.
//

#ifndef SERVER_CHATAPP_MESSAGE_H
#define SERVER_CHATAPP_MESSAGE_H

enum Status_Contact { sent, received, read };

using namespace std;

class Message {
private:
    int id,user_from,user_to,group_to;
    string message,sent_at;
    Status_Contact status;






    // CRUD
    bool save();
    bool update();
    bool remove();
};


#endif //SERVER_CHATAPP_MESSAGE_H
