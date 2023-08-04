
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"
#include "../../includes/Channel.hpp"

std::string Server::_getReason(std::string &buff) {
	std::string ret = "";
	size_t i = buff.find(':');

	if (i == buff.npos)
		return ret;
	ret.assign(buff.begin() + i + 1, buff.end());
	buff = buff.substr(0, i - 1);
	return ret;
}

static std::vector<std::string>	_strToVec(std::string buff) {
	std::string tmp;
	std::vector<std::string> chans;
	std::istringstream chans_buffstream(buff);

	while (std::getline(chans_buffstream, tmp, ','))
		if (!tmp.empty())
			chans.push_back(tmp);
	return chans;
}

void	Server::_sendPartMsg(User *sender, std::map<std::string, User *> targets, std::string chan_name, std::string msg) {
	for (std::map<std::string, User *>::iterator it = targets.begin(); it != targets.end(); it++) {
		if (msg.empty())
			_sendExecuted(it->second, RPL_PARTNOMSG(sender->getClient(), sender->getNick(), chan_name));
		else
			_sendExecuted(it->second, RPL_PARTMSG(sender->getClient(), sender->getNick(), chan_name, msg));
	}
}

int Server::_part(User *user, std::string buff) {
	if (buff.empty())
		return _sendError(user, ERR_NEEDMOREPARAMS(user->getClient(), user->getNick(), "PART"));
	std::string reason = _getReason(buff);
	std::vector<std::string> chans = _strToVec(buff);

	for (std::vector<std::string>::iterator it = chans.begin(); it != chans.end(); it++) {
		if (!_channels.count(*it)) {
			_sendError(user, ERR_NOSUCHCHANNEL(user->getClient(), user->getNick(), *it));
			continue;
		}
		Channel *chan = _channels.find(*it)->second;
		if (!chan->getUsers().count(user->getNick())){
			_sendError(user, ERR_NOTONCHANNEL(user->getClient(), user->getNick(), *it)));
			continue;
		}
		_sendPartMsg(user, chan->getUsers(), *it, reason);
		chan->removeUser(user);
		if (chan->getUsers().empty()) {
			std::map<std::string, Channel *>::iterator to_del = _channels.find(chan->getName());
			delete to_del->second;
			_channels.erase(to_del);
		}
	}
	return 0;
}
