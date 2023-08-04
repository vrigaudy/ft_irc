
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"

int Server::_quit(User *user, std::string args) {
	if (args.length() < 1)
		return _sendError(user, ERR_NEEDMOREPARAMS(user->getClient(), user->getNick(), "QUIT"));
	if (args[0] != ':')
		return _sendError(user, ERR_NOPREFIX(user->getClient(), user->getNick(), "QUIT"));
	args.erase(args.begin());
	_sendExecuted(user, RPL_QUIT((user->getClient()), args));
	std::map<std::string, Channel *> chans(user->getJoined());
	std::map<std::string, Channel *>::iterator ite = chans.end();
	for (std::map<std::string, Channel *>::iterator it = chans.begin(); it != ite; it++) {
		std::map<std::string, User *> users(it->second->getUsers());
		for (std::map<std::string, User *>::iterator it2 = users.begin(); it2 != users.end(); it2++) {
			_sendExecuted(it2->second, RPL_PARTMSG(user->getClient(), user->getNick(), it->first, args));
		}
	}
	return _disconnectUser(user, 0);
}
