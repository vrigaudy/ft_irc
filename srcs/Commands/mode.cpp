
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"
#include "../../includes/Channel.hpp"

int Server::_applyMode(User *user, std::string mode, bool value) {
	for (size_t i = 0; i < mode.length(); i++) {
		if (mode[i] == 'i')
			user->setInvisible(value);
		else if (mode[i] == 'o' && value == false)
			user->setOp(value);
		else
			_sendError(user, ERR_UMODEUNKNOWNFLAG(user->getClient(), user->getNick()));
	}
	return 0;
}

static std::vector<std::pair<char, std::string> > modeToVec(std::string mode, std::string arg) {
	size_t delimiter;
	std::vector<std::pair<char, std::string> > pairs;

	for (size_t i = 0; i < mode.size(); i++) {
		delimiter = arg.find(' ');
		if (delimiter != arg.npos) {
			pairs.push_back(std::make_pair(mode[i], std::string(arg.begin(), arg.begin() + delimiter)));
			arg.erase(arg.begin(), arg.begin() + delimiter + 1);
		}
		else {
			if (arg.empty())
				pairs.push_back(std::make_pair(mode[i], std::string()));
			else {
				pairs.push_back(std::make_pair(mode[i], std::string(arg.begin(), arg.end())));
				arg.erase(arg.begin(), arg.end());
			}
		}
	}
	return pairs;
}

int Server::_applyMode(User *user, Channel *channel, std::string buff, bool value) {
	size_t delimiter;
	std::string mode;
	std::string arg;
	std::vector<std::pair<char, std::string> > pairs;

	delimiter = buff.find(' ');
	if (delimiter == buff.npos) {
		mode = std::string(buff.begin(), buff.end());
		arg = "";
	}
	else {
		mode = std::string(buff.begin(), buff.begin() + delimiter);
		arg = std::string(buff.begin() + delimiter + 1, buff.end());
	}
	pairs = modeToVec(mode, arg);
	for (std::vector<std::pair<char, std::string> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
		if (it->first == 'l') {
			int limit;
			if (value && it->second.empty()) {
				_sendError(user, ERR_NEEDMOREPARAMS(user->getClient(), user->getNick(), "MODE"));
				continue;
			}
			else if (value && !(limit = atoi(it->second.c_str())))
				continue ;
			channel->setLimited(value, atoi(it->second.c_str()));
		}
		else if (it->first == 'k') {
			if (value && it->second.empty()) {
				_sendError(user, ERR_NEEDMOREPARAMS(user->getClient(), user->getNick(), "MODE"));
				continue;
			}
			if (value && channel->getKey().first) {
				_sendError(user, ERR_KEYSET(user->getClient(), user->getNick(), channel->getName()));
				continue;
			}
			channel->setKey(value, it->second);
		}
		else if (it->first == 'o') {
			if (value && it->second.empty()) {
				_sendError(user, ERR_NEEDMOREPARAMS(user->getClient(), user->getNick(), "MODE"));
				continue;
			}
			if (!channel->getUsers().count(it->second)) {
				_sendError(user, ERR_USERNOTINCHANNEL(user->getClient(), user->getNick(), it->second, channel->getName()));
				continue;
			}
			if (!value && it->second != user->getNick()) {
				_sendError(user, ERR_USERSDONTMATCH(user->getClient(), user->getNick()));
				continue;
			}
			if (!value) {
				if (channel->isOp(user))
					channel->removeFromOp(user);
				_sendExecuted(user, RPL_CHANNELMODEIS2(user->getClient(), user->getNick(), channel->getName(), "", it->second));
				continue;
			}
			channel->addToOp(channel->getUsers().find(it->second)->second);
			_sendExecuted(user, RPL_CHANNELMODEIS2(user->getClient(), user->getNick(), channel->getName(), "o", it->second));
		}
		else
			_sendError(user, ERR_UNKNOWNMODE(user->getClient(), user->getNick(), std::string(1, it->first), channel->getName()));
	}
	return 0;
}

int	Server::_mode(User *user, std::string buff) {
	bool value = false;
	size_t delimiter;
	std::string mode;
	std::string target;

	if (buff.empty())
		return _sendError(user, ERR_NEEDMOREPARAMS(user->getClient(), user->getNick(), "MODE"));
	delimiter = buff.find(' ');
	if (delimiter == buff.npos) {
		target = std::string(buff.begin(), buff.end());
		mode = "";
	}
	else {
		target = std::string(buff.begin(), buff.begin() + delimiter);
		mode = std::string(buff.begin() + delimiter + 1, buff.end());
	}
	if (!mode.empty()) {
		if (mode[0] == '+')
			value = true;
		if (mode[0] != '+' && mode[0] != '-')
			return _sendError(user, ERR_UMODEUNKNOWNFLAG(user->getClient(), user->getNick()));
		mode.erase(mode.begin());
	}
	if (target[0] != '#') {
		std::map<int, User *>::iterator it;
		for (it = _users.begin(); it != _users.end(); it++)
			if (it->second->getNick() == buff)
				break;
		if (--it == _users.end())
			return _sendError(user, ERR_NOSUCHNICK(user->getClient(), user->getNick(), target));
		if (user->getNick() != target)
			return _sendError(user, ERR_USERSDONTMATCH(user->getClient(), user->getNick()));
		if (!mode.empty())
			_applyMode(user, mode, value);
		return _sendExecuted(user, RPL_UMODEIS(user->getClient(), user->getNick(), user->getModes()));
	}
	else {
		Channel *channel_moded = NULL;
		if (!_channels.count(target))
			return _sendError(user, ERR_NOSUCHCHANNEL(user->getClient(), user->getNick(), target));
		channel_moded = _channels[target];
		if (!mode.empty() && !channel_moded->isOp(user))
			return _sendError(user, ERR_CHANOPRIVSNEEDED(user->getClient(), user->getNick(), channel_moded->getName()));
		if (!mode.empty())
			_applyMode(user, _channels[target], mode, value);
		return _sendExecuted(user, RPL_CHANNELMODEIS(user->getClient(), user->getNick(), channel_moded->getName(), channel_moded->getModes()));
	}
	return 0;
}
