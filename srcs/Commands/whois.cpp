
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"

int Server::_whois(User *user, std::string buff) {
	bool found = 0;

	if (buff.empty())
		_sendError(user, ERR_NONICKNAMEGIVEN(user->getClient(), user->getNick()));
	else {
		for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
			if (it->second->getNick() == buff) {
				_sendExecuted(user, RPL_WHOISUSER(user->getClient(), user->getNick(), it->second->getNick(), it->second->getUserName(), it->second->getHostName(), it->second->getRealName()));
				found = 1;
			}
	}
	if (!found)
		_sendError(user, ERR_NOSUCHNICK(user->getClient(), user->getNick(), buff));
	return _sendExecuted(user, RPL_ENDOFWHOIS(user->getClient(), user->getNick(), buff));
}
