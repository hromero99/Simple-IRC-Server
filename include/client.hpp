#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#define MAX_BUFFER_LENGTH 255
class Client{
private:
    struct sockaddr_in _serverAddress;
    int _socket;
    socklen_t _serverAddressLength;
    fd_set _readfds;
    fd_set _auxfds;
    std::string _channel;
public:
    Client(std::string serverAddress, int serverPort);
    void connectIRCServer();
    void setAuxFds();
    bool validateMessage(std::string message);
    void sendMessage(const std::string &message);
    int lookForConnections();
    inline void setChannel(std::string channel){_channel = channel;};
    inline std::string getChannel()const{return _channel;};
    std::string checkIfHasMessages();
};

#endif