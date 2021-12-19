//
// Created by Zuzana Žillová on 19. 12. 2021.
//

#ifndef SERVER_CHATAPP_GROUPUSER_H
#define SERVER_CHATAPP_GROUPUSER_H


class GroupUser {
    int group_id, user_id;

    // CRUD
    bool save();
    bool update();
    bool remove();
};


#endif //SERVER_CHATAPP_GROUPUSER_H
