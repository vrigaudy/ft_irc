
#include "Server.hpp"

// Constructors
Server::Server () {}

Server::Server (std::string port, std::string password, struct tm *timeinfo):
		_servinfo(NULL),
		_serv_socket_fd(0),
		_port(port),
		_password(password)
{
	std::cout << "Initializing server ..." << std::endl;
	memServer::set(_hints, 0, sizeof(_hints));
	this->Server::setDatetime(timeinfo);
	std::cout << "Server started to listen" << std::endl;
}

// Destructor
Server::Server () {
	std::cout << "Shutting down the server" << std::endl;
}

// Setters
void	Server::setHints() {
	_hints.ai_family = AF_INET;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_flags = AI_PASSIVE;
}

void	Server::setPassword(std::string new_password) {
	_password = new_password;
}

void	Server::setDatetime(struct tm *timeinfo) {
	char	buffer[80];
	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
	std::string str(buffer);
	_datetime = str;
}

void	Server::setMotd(std::string new_motd) {
	_motd = new_motd;
}

// Getters
std::string						Server::getPort() const { 
	return _port; 
}

std::string						Server::getPassword() const {
	return _password;
}

std::string						Server::getDatetime() const {
	return _datetime;
}

std::string						Server::getMotd() const {
	return _motd;
}

std::map<std::string, Channel>&	Server::getChannel() {
	return _channels;
}

std::map<int const, User>&		Server::getUser() {
	return _users;
}

std::vector<server_op>&			Server::getOperator() {
	return _irc_operators;
}

// Error catcher
char const *	Server::BadClient::what() const throw () {
	return "Invalid client: please provide valid information"
}
