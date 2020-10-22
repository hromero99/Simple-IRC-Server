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

void Channel::sendMessageToAllClients(std::string message, std::string username) {
    message = _name + ":"+ username + ":"+message;
    char buffer[255];
    bzero(buffer, 255);
    strcpy(buffer,message.c_str());
    std::list<ServerClient>::iterator it = _clients.begin();
    for (; it != _clients.end(); it++){
        if (send(it->getDescriptor(), buffer, strlen(buffer), 0) < 0){
            std::cout<<"Error sending message "<<message<<"in channel "<<_name<<std::endl;
        }
    }
}
bool Channel::checkIfUserIsInChannel(std::string username){
    std::list<ServerClient>::iterator it = _clients.begin();
    for (; it != _clients.end(); it++){
        if (it->getUsername() == username){
            return true;
        }
    }
    return false;
}

bool Channel::dropUserFromChannel(const std::string &username){
    std::list<ServerClient>::iterator it = _clients.begin();
    for (; it != _clients.end(); it++){
        if (it->getUsername() == username){
            _clients.erase(it);
            return true;
        }
    }
    return false;
}
