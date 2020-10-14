#include "server.hpp"


void Server::addChannelHandler(std::string clientMessage, ServerClient client) {
    int position = clientMessage.find(" ");
    std::string channelName = clientMessage.substr(position + 1, clientMessage.length());
    //Check if Channel already exists
    std::vector<Channel>::iterator it = _channels.begin();
    if (checkIfChannelExistsInServer(channelName)) {
        sendMessageToClient(client.getDescriptor(), "-ERR Channel " + channelName + "already in system");
    }
    else {
        Channel channel = Channel(channelName);
        channel.addNewClient(client);
        _channels.emplace_back(channel);
        sendMessageToClient(client.getDescriptor(), "+OK. Channel Created");
    }
}