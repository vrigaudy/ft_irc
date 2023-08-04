
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"

int Server::_pong(User *user, std::string buff) {
	static_cast<void>(buff);
	return _sendExecuted(user, "PONG irc.server\r\n");
}
