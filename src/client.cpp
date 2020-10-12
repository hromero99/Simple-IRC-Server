#include "client.hpp"

Client::Client(std::string serverAddress, int serverPort ){
    _socket = socket(AF_INET,SOCK_STREAM,0);
    if (_socket < 0){
        std::cout<<"Error opening socket"<<std::endl;
        exit(EXIT_FAILURE);
    }
    _serverAddress.sin_family = AF_INET;
    _serverAddress.sin_addr.s_addr=inet_addr(serverAddress.c_str());
    _serverAddress.sin_port=htons(serverPort);
    _serverAddressLength = sizeof(_serverAddress);
    // Set to 0 ( initialize FD SETS)
    FD_ZERO(&_readfds);
    FD_ZERO(&_auxfds);
    //Add Socket Descriptor to readfds
    FD_SET(_socket,&_readfds);
    FD_SET(0, &_readfds);
}

void Client::connectIRCServer(){
    if (connect(_socket,(struct sockaddr *)  &_serverAddress, _serverAddressLength) < 0){
        std::cout<<"Error connecting to server"<<std::endl;
        exit(EXIT_FAILURE);
    }
}
void Client::setAuxFds(){
    _auxfds = _readfds;
}
bool Client::validateMessage(std::string message){
    return true;
}
void Client::sendMessage(const std::string & message){
    std::string finalMessage = message + '\0';
    if (send(_socket,finalMessage.c_str(),finalMessage.length(),0) < 0){
        std::cout<<"Error enviando el mensaje "<<message<<" "<<errno<<std::endl;
    }
}

std::string Client::checkIfHasMessages(){
    int nReceivedBytes = 0;
    std::vector<char> buffer(MAX_BUFFER_LENGTH);
    std::string stringBuffer;
    if(FD_ISSET(_socket, &_auxfds)){
        // Make a look to receive all char elements from buffer
        do {
            //recv returns the N bytes received
            nReceivedBytes = recv(_socket,&buffer[0],buffer.size(),0);
            if (nReceivedBytes == -1){
            }
            else{
                stringBuffer.append(buffer.cbegin(), buffer.cend());
            }
        }while(nReceivedBytes == MAX_BUFFER_LENGTH);

        if(stringBuffer == "Demasiados clientes conectados\n"){
            return stringBuffer;
        }
        if(stringBuffer == "Desconexión servidor\n"){
            return stringBuffer;
        }
        return stringBuffer;
    }
    return "None";
}

int Client::lookForConnections(){
    int salida = accept(_socket + 1, (struct sockaddr *)&_serverAddress, &_serverAddressLength);
    if (salida < 0){
        std::cout<<"Error aceptando la conexion"<<std::endl;
    }
    return salida;
}
