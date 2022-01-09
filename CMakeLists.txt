cmake_minimum_required(VERSION 3.7)
project(Server_ChatAPP)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
include_directories(.)

add_executable(
        Server_ChatAPP
        main.cpp
        models/User.cpp
        models/User.h
        models/Group.cpp
        models/Group.h
        models/Message.cpp
        models/Message.h
        models/Contact.cpp
        models/Contact.h
        JsonReader.cpp
        JsonReader.h
        json.hpp
        controllers/AuthController.cpp
        controllers/AuthController.h
        controllers/MessageController.cpp
        controllers/MessageController.h
        controllers/ContactsController.cpp
        controllers/ContactsController.h
        controllers/GroupsController.cpp
        controllers/GroupsController.h
        Navigator.cpp Navigator.h
        Helpers.cpp Helpers.h
        controllers/RequestsController.cpp
        controllers/RequestsController.h
        providers/ActiveUsersProvider.cpp
        providers/ActiveUsersProvider.h
        controllers/UserController.cpp
        controllers/UserController.h
        Cryptograph.cpp Cryptograph.h
)




