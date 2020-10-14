#include "channel.hpp"


Channel::Channel(std::string channelName){
  _name = channelName;
}

bool Channel::addNewClient(ServerClient client){
  _clients.push_back(client);
  return true;
}

bool Channel::removeClient(ServerClient client) {
    int position = 0;
    std::list<ServerClient>::iterator it = _clients.begin();
    for (; it != _clients.end();it++){
        if (it -> getUsername() == client.getUsername()){
            _clients.erase(it);
            return true;
        }
        position ++;
    }
    return false;
}