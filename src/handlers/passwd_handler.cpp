#include "server.hpp"

void Server::passwdHandler(std::string clientMessage, ServerClient client){
    // Check if user is logged and the save database for changes
    int position = clientMessage.find(" ");
    std::string password = clientMessage.substr(position+1, clientMessage.length());
    client.setPassword(password);
    updateClient(client);
    // Check if user is in database otherwise must be added
    if (_database->checkIfClientExists(client.getUsername())){
        if (_database->checkIfUserPasswordIsCorrect(client.getUsername(),client.getPassword())){
            sendMessageToClient(client.getDescriptor(), "+Ok. User authenticated");
            client.setStatus(1);
        }
        else{
            sendMessageToClient(client.getDescriptor(), "-ERR. User password not valid");
        }
    }
    else{
        _database->addClient(client);
        sendMessageToClient(client.getDescriptor(), "+Ok. User authenticated");
    }
}