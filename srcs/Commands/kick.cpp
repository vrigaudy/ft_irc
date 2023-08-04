
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"
#include "../../includes/Channel.hpp"

int	Server::_kick(User *user, std::string buff) {
	if (buff.empty())
		return _sendError(user, ERR_NEEDMOREPARAMS(user->getClient(), user->getNick(), "KICK"));
	std::string reason = _getReason(buff);
	size_t delimiter;
	std::string chan;
	std::string to_kick;
	if ((delimiter = buff.find(' ')) == buff.npos)
		return _sendError(user, ERR_NEEDMOREPARAMS(user->getClient(), user->getNick(), "KICK"));
	chan = std::string(buff.begin(), buff.begin() + delimiter);
	to_kick = std::string(buff.begin() + delimiter + 1, buff.end());
	if (!_channels.count(chan))
		return _sendError(user, ERR_NOSUCHCHANNEL(user->getClient(), user->getNick(), chan));
	if (!user->getJoined().count(chan))
		return _sendError(user, ERR_NOTONCHANNEL(user->getClient(), user->getNick(), chan)));
	Channel *channel = _channels[chan];
	if (!user->isOp(channel))
		return _sendError(user, ERR_CHANOPRIVSNEEDED(user->getClient(), user->getNick(), chan));
	if (!channel->getUsers().count(to_kick))
		return _sendError(user, ERR_USERNOTINCHANNEL(user->getClient(), user->getNick(), to_kick, channel->getName()));
	std::map<std::string, User *> targets = channel->getUsers();
	if (reason.empty())
		reason = "You've been kicked without reason";
	for (std::map<std::string, User *>::iterator it = targets.begin(); it != targets.end(); it++)
		_sendExecuted(it->second, RPL_KICK(user->getClient(), user->getNick(), channel->getName(), to_kick, reason));
	User *tmp = NULL;
	std::map<int, User *>::iterator it = _users.begin();
	for (; it != _users.end(); it++) {
		if (it->second->getNick() == to_kick) {
			tmp = it->second;
			break;
		}
	}
	channel->removeUser(tmp);
	return 0;
}
