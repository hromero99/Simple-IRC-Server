#include "server.hpp"

void Server::listUsersHandler(ServerClient client) {
    std::vector<ServerClient>::iterator it = _clients.begin();
    std::string userLists, username;
    for (; it != _clients.end(); it++){
        username = it -> getUsername();
        userLists += username +";";
    }
    sendMessageToClient(client.getDescriptor(),userLists);
}