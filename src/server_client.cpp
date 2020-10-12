#include "server_client.hpp"

ServerClient::ServerClient(int serverSocket) {
    _serverSocket = serverSocket;
    // Status default is not created, because the user is created when is login and can send messages
    _status = -1;
}

void ServerClient::login(std::string MessageBuffer){
    // Get the message with format USER username
    // Split The message to get username
    // Find first (and unique) position of " " character
    std::size_t position = MessageBuffer.find(" ");
    std::string username = MessageBuffer.substr(position+1, MessageBuffer.size());
    setUsername(username);
    _status = 1;
}