#include "channel.hpp"


Channel::Channel(std::string channelName){
  _name = channelName;
}

bool Channel::addNewClient(int clientSocketDescriptor){
  _clients.push_back(clientSocketDescriptor);
  return true;
}
