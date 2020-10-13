#include "server.hpp"

Server::Server(std::string user_file){
    //Initialize socket and sockaddr struct for server object
    _socket = socket(AF_INET, SOCK_STREAM,0);
    if (_socket < 0){
        std::cout<<"Error creating socket "<<errno<<std::endl;
        exit(EXIT_FAILURE);
    }
    _Nclients = 0;
    _maxClients = MAX_USERS;
    _ip.sin_family = AF_INET;
    _ip.sin_port = htons(2000);
    _ip.sin_addr.s_addr = INADDR_ANY;

    // Set to 0 ( initialize FD SETS)
    FD_ZERO(&_readfds);
    FD_ZERO(&_auxfds);
    //Add Socket Descriptor to readfds
    FD_SET(_socket,&_readfds);
    FD_SET(0, &_readfds);
    // Create the main channel for default
    _database = new Database(user_file);
    _database->loadDatabase();
}

void Server::setAuxFds(){
    _auxfds = _readfds;
}

void Server::bindServer(){
    if (bind(_socket,(struct sockaddr *) &_ip, sizeof(_ip) ) == -1 ){
        std::cout<<"Error in bind function "<<errno<<std::endl;
        exit(EXIT_FAILURE);
    }

    if(listen(_socket,1) == -1){
		perror("Error en la operación de listen");
		exit(EXIT_FAILURE);
	}
}

void Server::sendMessageToClient(int socket, std::string message){
    char buffer[255];
    bzero(buffer,255);
    strcpy(buffer,message.c_str());
    if (send(socket, buffer,strlen(buffer), 0) < 0){
        std::cout<<"Error enviando el mensaje al cliente "<<socket<<std::endl;
    }

}

int Server::getClientsOutput(){
    int output;
    output = select(FD_SETSIZE, &_auxfds, NULL,NULL,NULL);
    return output;
}

void Server::lookForConnectionSocket(){
    int new_socket;
    struct sockaddr_in from;
    socklen_t from_length = sizeof(from);
    std::vector<char> message_from_client(255);
    for (int clientSocket=0; clientSocket<FD_SETSIZE; clientSocket++){
        //Check if the descriptor i is still in the aux set. If is return 1 else returns 0
        if (FD_ISSET(clientSocket, &_auxfds)) {
            // Check if the descriptor is same as socket descriptor must create new socket
            // This condition is for a new client who request server information and isn't in FD_SET
            if (clientSocket == _socket) {
                //Accept connection and check if has error
                new_socket = accept(_socket, (struct sockaddr *) &from, &from_length);
                if ( new_socket == -1) {
                    std::cout << "Error while accepting connection " << errno << std::endl;
                }
                // if socket has not errors
                else {
                    //Check if number of clients is valid
                    if (_Nclients < 255) {
                        _clientsDescriptors[_Nclients] = new_socket;
                        // Create new Client object and associate with new socket
                        //_clients.emplace_back(ServerClient(new_socket));
                        _Nclients++;
                        FD_SET(new_socket, &_readfds);
                        sendMessageToClient(new_socket, "+0k. User connected\n");

                        // Send to new client Welcome message
                        // notifyAllClients("Nuevo cliente en el servidor\n");
                    }
                        // if there are a lot of clients, notify to new host
                    else {
                        _serverMessages = "Hay demasiados clientes conectados";
                        send(new_socket, _serverMessages.c_str(), strlen(_serverMessages.c_str()), 0);
                        close(new_socket);
                    }
                }
            }
            else{
                int received;
                std::string clientMessage;
                char clientBuffer[MAX_BUFFER_LENGTH];
                bzero(clientBuffer, MAX_BUFFER_LENGTH);
                received = recv(clientSocket,&clientBuffer,MAX_BUFFER_LENGTH,0);
                if (received < 0){
                    std::cout<<"Error recibiendo mensajes del cliente"<<std::endl;
                }
                clientMessage = std::string(clientBuffer);
                processClientMessage(clientSocket, clientMessage);
            }
        }
        // If the client has a previous connection the socket must be in a FD_SET and don't match with _socket descriptor

    }
}

void Server::shutdown(){
    close(_socket);
}

void Server::notifyAllClients(std::string message){
    for (int i=0;i<_Nclients;i++){
        if (send(_clientsDescriptors[i], message.c_str(), message.length(), 0 ) < 0){
            std::cout<<"Error sending message to client "<<errno<<std::endl;
        }
    }
}

ServerClient Server::getClientFromList(int clientSocket){
    ServerClient client = ServerClient(-1);
    for (std::vector<ServerClient>::iterator it = _clients.begin(); it != _clients.end(); it++){
        if ( it->getDescriptor() == clientSocket ){
            client = *it;
        }
    }
    return client;
}

bool Server::checkIfChannelExists(std::string channelName){
  for(std::vector<Channel>::iterator it = _channels.begin(); it!= _channels.end();it++){
    if (it->getChannelName() == channelName){
      return true;
    }
  }
  return false;
}

bool Server::addNewChannel(std::string newChannelName){
  if (checkIfChannelExists(newChannelName)){
    Channel channel(newChannelName);
    _channels.push_back(channel);
    return true;
  }
  return false;
}

std::string Server::getCommandFromClientMessage(std::string basicString) {
    std::size_t position = basicString.find(" ");
    return basicString.substr(0, position);
}
void Server::updateClient(ServerClient newClient){
    for(std::vector<ServerClient>::iterator it = _clients.begin(); it!= _clients.end();it++){
        if (it->getDescriptor() == newClient.getDescriptor()){
            *it = newClient;
        }
    }
}
void Server::processClientMessage(int clientDescriptor, std::string clientMessage){
    ServerClient client = getClientFromList(clientDescriptor);
    // Check if client descriptor is -1 because is that does not exists and assigns new descriptor and add to list
    if (client.getDescriptor() == -1){
        client.setDescriptor(clientDescriptor);
        _clients.emplace_back(client);
    }
    std::string command = getCommandFromClientMessage(clientMessage);
    std::cout<<"COMANDO: "<<command<<std::endl;

    if (command == "USER"){
       int position = clientMessage.find(" ");
       std::string username = clientMessage.substr(position+1, clientMessage.length());
       client.setUsername(username);
       updateClient(client);
       sendMessageToClient(clientDescriptor, "+Ok. User registered");
    }

    else if (command == "PASSW"){
        // Check if user is logged and the save database for changes
        int position = clientMessage.find(" ");
        std::string password = clientMessage.substr(position+1, clientMessage.length());
        client.setPassword(password);
        updateClient(client);
        // Check if user is in database otherwise must be added
        if (_database->checkIfClientExists(client.getUsername())){
            if (_database->checkIfUserPasswordIsCorrect(client.getUsername(),client.getPassword())){
                sendMessageToClient(client.getDescriptor(), "+Ok. User authenticated");
                client.setStatus(1);
            }
            else{
                sendMessageToClient(client.getDescriptor(), "-ERR. User password not valid");
            }
        }
        else{
            _database->addClient(client);
            sendMessageToClient(client.getDescriptor(), "+Ok. User authenticated");
        }
    }

    else {
        sendMessageToClient(clientDescriptor, "-ERR. Invalid command");
    }
}


