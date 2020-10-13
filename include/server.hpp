#ifndef _SERVER_H_
#define _SERVER_H_
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <csignal>
#include <unistd.h>
#include <ctime>
#include <arpa/inet.h>
#include <vector>
#include <string.h>
#include "channel.hpp"
#include "server_client.hpp"
#include "server_client.hpp"
#include "database.hpp"
#define MAX_BUFFER_LENGTH 255
#define MAX_USERS 100

class Server{
    private:
        int _socket;
        struct sockaddr_in _ip;
        struct sockaddr_in _receiveMsg;
        fd_set _readfds;
        fd_set _auxfds;
        int _maxClients;
        int _Nclients;
        int _clientsDescriptors[255];
        std::vector<ServerClient> _clients;
        std::string _serverMessages;
        std::vector<Channel> _channels;
        Database* _database;

    public:
        Server(std::string user_file);
        void bindServer();
        void setAuxFds();
        int getClientsOutput();
        void lookForConnectionSocket();
        void shutdown();
        void notifyAllClients(std::string message);
        void processClientMessage(int clientDescriptor, std::string clientMessage);
        bool addNewChannel(std::string newChannelName);
        bool checkIfChannelExists(std::string channelName);
        void sendMessageToClient(int socket, std::string message);
        bool addNewClient(ServerClient newClient);
        ServerClient getClientFromList(int clientSocket);
        void updateClient(ServerClient newClient);

        // handlers
        void passwdHandler(std::string clientMessage, ServerClient client);
        void userHandler(std::string clientMessage, ServerClient client);
        std::string getCommandFromClientMessage(std::string basicString);
};
#endif
