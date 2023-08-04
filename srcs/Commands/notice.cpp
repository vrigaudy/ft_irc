
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"

int Server::_notice(User *user, std::string buff) {
	std::pair<std::string, std::string> recip = _splitPrivMsg(buff);
	if (recip.first.empty())
		return 1;
	if (recip.second.empty())
		return 1;

	std::map<std::string, User *> targets;
	if (recip.first[0] == '#') {
		if (!_channels.count(recip.first))
			return 1;
		Channel *chan = _channels.find(recip.first)->second;
		targets = chan->getUsers();
	}
	else {
		std::map<int, User *>::iterator it;
		for (it = _users.begin(); it != _users.end(); it++) {
			if ((*it).second->getNick() == recip.first) {
				targets.insert(std::pair<std::string, User *> ((*it).second->getNick(), (*it).second));
				break;
			}
		}
		if (targets.empty())
			return 1;
	}
	for (std::map<std::string, User *>::iterator it = targets.begin(); it != targets.end(); it++)
		if (it->second != user)
			_sendPrivMsg(user, it->second, recip.first, recip.second, " NOTICE ");
	return 0;
}
