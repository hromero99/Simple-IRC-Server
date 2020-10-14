#include "server.hpp"

void Server::listChatsHandler(ServerClient client) {
    std::string finalMessage = "CHATS ";
    std::vector<Channel>::iterator it = _channels.begin();
    for (; it != _channels.end(); it++){
        finalMessage += it->getChannelName() + ";";
    }
    sendMessageToClient(client.getDescriptor(), finalMessage);
}
