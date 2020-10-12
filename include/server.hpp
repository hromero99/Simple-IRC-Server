#ifndef _SERVER_H_
#define _SERVER_H_
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <vector>
#include "channel.hpp"
#include "server_client.hpp"
#include "server_client.hpp"
#define MAX_BUFFER_LENGTH 255

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

    public:
        Server(int maxClients=1);
        void bindServer();
        void setAuxFds();
        int getClientsOutput();
        void lookForConnectionSocket();
        void shutdown();
        void notifyAllClients(std::string message);
        void proccessClientMessage(int clientDescriptor);
        bool addNewChannel(std::string newChannelName);
        bool checkIfChannelExists(std::string channelName);
        void sendMessageToClient(int socket, std::string message);
        bool addNewClient(ServerClient newClient);
        ServerClient getClientFromList(int clientSocket);

    std::string getCommandFromClientMessage(std::string basicString);
};
#endif
