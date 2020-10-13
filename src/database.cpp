#include "database.hpp"

Database::Database(std::string username_file) {
    //TODO: Implement checking if file exists
    _username_file = username_file;
    loadDatabase();
}

void Database::loadDatabase() {
    std::ifstream file(_username_file);
    std::string username, password, buffer;
    size_t positionDelimiter;
    while(std::getline(file,buffer)){
        ServerClient client(-1);
        positionDelimiter = buffer.find(";");
        username = buffer.substr(0, positionDelimiter);
        password = buffer.substr(positionDelimiter + 1, buffer.size());
        client.setUsername(username);
        client.setPassword(password);
        _clients.emplace_back(client);
    }
    file.close();
}

void Database::saveDatabase(){
    std::ofstream file(_username_file);
    std::string outputLine;
    for (std::vector<ServerClient>::iterator it = _clients.begin(); it != _clients.end(); it++ ){
        outputLine = it->getUsername() + ";" + it->getPassword();
        std::cout<<outputLine<<std::endl;
        file<<outputLine;
    }
    file.close();
}

bool Database::addClient(ServerClient newClient) {
    _clients.emplace_back(newClient);
    saveDatabase();
    return true;
}

bool Database::checkIfClientExists(std::string clientUsername) {
    for (std::vector<ServerClient>::iterator it = _clients.begin(); it != _clients.end(); it++){
        if (clientUsername == it->getUsername()){
            return true;
        }
    }
    return false;
}

bool Database::checkIfUserPasswordIsCorrect(std::string username, std::string password) {
    //Look for ServerUser object in list and then check if password is same as the file
    loadDatabase(); //For load the last changes on database
    if (checkIfClientExists(username)) {
        for (std::vector<ServerClient>::iterator it = _clients.begin(); it != _clients.end(); it++) {
            if ((it->getUsername() == username) && (it->getPassword() == password)) {
                return true;
            }
        }
    }
    return false;
}