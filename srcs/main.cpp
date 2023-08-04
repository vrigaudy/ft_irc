
#include <iostream>
#include "../includes/Server.hpp"
#include "../includes/Exception.hpp"

#define ARG_ERR "ircserv: 2 arguments needed:\n\nUsage is: ./ircserv <port> <password>\n\t<port>: port number on wich your IRC server will be listening to for incoming IRC connections\n\t<password>: it will be needed by any IRC client that tries to connect to your server"
#define PORT_ERR  "Invalid port, use only number between 1024 and 65535"
#define PASSWORD_ERR "Password must not be empty"

bool stop = 0;

void sig_handler(int sig) {
	if (sig == SIGINT || sig == SIGQUIT)
		stop = 1;
}

bool	check_input(int ac, char **av)
{
	if (ac != 3) {
		std::cerr << ARG_ERR << std::endl;
		return 0;
	}
	const std::string port(av[1]);
	std::string::const_iterator it = port.begin();
	for (; it != port.end(); it++) {
		if (!std::isdigit(*it)) {
			std::cerr << PORT_ERR << std::endl;
			return 0;
		}
	}
	if (port.length() == 5 || port.length() == 4) {
		int portNb = atoi(port.c_str());
		if (portNb < 1024 || portNb > 65535) {
			std::cerr << PORT_ERR << std::endl;
			return 0;
		}
	}
	else {
		std::cerr << PORT_ERR << std::endl;
		return 0;
	}
	const std::string password(av[1]);
	if (password.empty()) {
		std::cerr << PASSWORD_ERR << std::endl;
		return 0;
	}
	return 1;
}

int	main(int ac, char **av) {
	if (!check_input(ac, av))
		return 1;
	Server *server = new Server(av[1], av[2]);
	try {
		server->setup();
	}
	catch(const std::exception &e) {
		std::cerr << ORANGE BOLD "[ircserv]" RED " Server couldn't be created:" RESET RED << std::endl;
		std::cerr << e.what() << std::strerror(errno) << RESET << std::endl;
		delete server;
		return 1;
	}
	while (!stop) {
		try {
			signal(SIGINT, sig_handler);
			signal(SIGQUIT, sig_handler);
			server->launch();
		}
		catch(const std::exception &e) {
			std::cerr << RED << e.what() << std::strerror(errno) << RESET << std::endl;
			delete server;
			return 1;
		}
	}
	delete server;
	return 0;
}
