#include "server.hpp"


void Server::addChannelHandler(std::string clientMessage, ServerClient*  client) {
    int position = clientMessage.find(" ");
    std::string channelName = clientMessage.substr(position + 1, clientMessage.length());
    //Check if Channel already exists

    if (checkIfChannelExistsInServer(channelName) and _channels.size() <= MAX_CHANNELS and !(checkIfUserIsOwner(client->getUsername()))) {
        sendMessageToClient(client->getDescriptor(), "-ERR Channel " + channelName + "already in system");
    }
    else if (_channels.size() >=MAX_CHANNELS){
       sendMessageToClient(client->getDescriptor(), "-Err. It is not possible to ad more channels");
    }
    else if ((checkIfUserIsOwner(client->getUsername()))){
        sendMessageToClient(client->getDescriptor(), "-Err. You can't add other channel");
    }
    else {
        client->setChannel(channelName);
        Channel channel = Channel(channelName);
        channel.addNewClient(*client);
        channel.setOwner(client->getUsername());
        _channels.emplace_back(channel);
        //Move client to new channel
        moveUserToOtherChannel(client, client->getChannel(), channel.getChannelName());
        sendMessageToClient(client->getDescriptor(), "+OK. Channel Created");
    }
}