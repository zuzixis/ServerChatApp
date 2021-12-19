//
// Created by Zuzana Žillová on 19. 12. 2021.
//

#ifndef SERVER_CHATAPP_CONTACT_H
#define SERVER_CHATAPP_CONTACT_H

enum Status_Message { waiting, confirmed };

class Contact {
    int id,user_1,user_2;
    Status_Message status;

    // CRUD
    bool save();
    bool update();
    bool remove();
};


#endif //SERVER_CHATAPP_CONTACT_H
