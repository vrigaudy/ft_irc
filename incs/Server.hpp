
#ifndef SERVER_HPP

# define SERVER_HPP

# include "Irc.hpp"
# include "Channel.hpp"
# include "User.hpp"

class	server {
	private:
		struct addrinfo					_hints;
		struct addrinfo					*_servinfo;

		int								_serv_socket_fd;

		std::string						_password;
		std::string						_datetime;
		std::string						_motd;
		std::string						_port;

		std::map<std::string, Channel>	_channels;

		std::map<int const, User>		_users;

		std::vector<server_op>			_irc_operators;

		// Constructor
		Server();

	public:
		// Constructor
		Server(std::string port, std::string password, struct tm *timeinfo);

		// Destructor
		~Server();

		// Setters
		void	setHints();
		void	setPassword(std::string new_password);
		void	setDatetime(struct tm *timeinfo);
		void	setMotd(std::string new_motd);

		// Getters
		std::string	getPort() const;
		std::string	getPassword() const;
		std::string	getDatetime() const;
		std::string	getMotd() const;

		std::map<std::string, Channel>&	getChannel();

		std::map<int const, User>&		getUser();

		std::vector<server_op>&			getOperator();

		// Error catcher
		char const *	BadClient::what() const throw ();
};

#endif
