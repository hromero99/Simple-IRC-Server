#ifndef SIMPLE_IRC_DATABASE_H
#define SIMPLE_IRC_DATABASE_H
#include <iostream>
#include <fstream>
#include <vector>
#include "server_client.hpp"

class Database{
    private:
        std::string _username_file;
        std::vector<ServerClient> _clients;
    public:
        Database(std::string username_file);
        void loadDatabase();
        void saveDatabase();
        std::vector<ServerClient> find_user(std::string username);
        bool addClient(ServerClient newClient);
        bool checkIfClientExists(std::string clientUsername);
        bool checkIfUserPasswordIsCorrect(std::string username, std::string password);
};
#endif