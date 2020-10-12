#ifndef _CHANNEL_H_
#define _CHANNEL_H_
#include <iostream>
#include <vector>

class Channel{
  private:
    std::string _name;
    std::vector<int> _clients;
  public:
    Channel(std::string channelName);
    bool addNewClient(int clientSocketDescriptor);
    inline std::string getChannelName()const {return _name;};
};



#endif
