#include "server.hpp"

void Server::userHandler(std::string clientMessage, ServerClient client){
    int position = clientMessage.find(" ");
    std::string username = clientMessage.substr(position+1, clientMessage.length());
    client.setUsername(username);
    updateClient(client);
    sendMessageToClient(client.getDescriptor(), "+Ok. User registered");
}
