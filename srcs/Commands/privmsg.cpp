
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"

std::pair<std::string, std::string>	Server::_splitPrivMsg(std::string buff) {
	size_t i = buff.find(':');
	if (i == buff.npos)
		return std::make_pair(std::string(buff.begin(), buff.end()), std::string(""));
	std::string first(buff.begin(), buff.begin() + i);
	std::string second(buff.begin() + i + 1, buff.end());

	i = first.find(' ');
	if (i != first.npos)
		first.erase(first.begin() + i, first.end());
	return std::make_pair(std::string(first), std::string(second));
}

void	Server::_sendPrivMsg(User *sender, User *target, std::string chan_name, std::string msg, std::string cmd_type) {
	std::string rpl = ":" + sender->getNick() + cmd_type + chan_name + " " + msg + "\r\n";
	_sendExecuted(target, rpl);
}

int		Server::_privmsg(User *user, std::string buff) {
	std::pair<std::string, std::string> recip = _splitPrivMsg(buff);
	if (recip.first.empty())
		return _sendError(user, ERR_NORECIPIENT(user->getClient(), user->getNick()));
	if (recip.second.empty())
		return _sendError(user, ERR_NOTEXTTOSEND(user->getClient(), user->getNick()));

	std::map<std::string, User *> targets;
	if (recip.first[0] == '#') {
		if (!_channels.count(recip.first))
			return _sendError(user, ERR_NOSUCHCHANNEL(user->getClient(), user->getNick(), recip.first));
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
			return _sendError(user, ERR_NOSUCHNICK(user->getClient(), user->getNick(), recip.first));
	}
	for (std::map<std::string, User *>::iterator it = targets.begin(); it != targets.end(); it++)
		if (it->second != user)
			_sendPrivMsg(user, it->second, recip.first, recip.second, " PRIVMSG ");
	return 0;
}
