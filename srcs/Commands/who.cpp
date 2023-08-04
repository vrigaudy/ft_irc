
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"

int Server::_who(User *user, std::string buff) {
	if (buff.empty())
		return _sendError(user, ERR_NEEDMOREPARAMS(user->getClient(), user->getNick(), "WHO"));
	std::string rpl = "";

	if (buff[0] == '#') {
		if (!_channels.count(buff))
			return _sendError(user, ERR_NOSUCHCHANNEL(user->getClient(), user->getNick(), buff));
		Channel *chan = _channels.find(buff)->second;
		std::map<std::string, User *> targets = chan->getUsers();
		for (std::map<std::string, User *>::iterator it = targets.begin(); it != targets.end(); it++) {
			if (chan->isOp(it->second))
				rpl = chan->getName() + " " + it->second->getUserName() + " " + it->second->getHostName() + " irc.serverv " + it->second->getNick() + " H@ :0 " + it->second->getRealName();
			else
				rpl = chan->getName() + " " + it->second->getUserName() + " " + it->second->getHostName() + " irc.serverv " + it->second->getNick() + " H :0 " + it->second->getRealName();
			_sendExecuted(user, RPL_WHOREPLY(user->getClient(), user->getNick(), rpl));
			rpl.clear();
		}
		return _sendExecuted(user, RPL_ENDOFWHO(user->getClient(), user->getNick(), buff));
	}
	bool sent = false;
	for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++) {
		if (it->second->getNick() == buff) {
			std::map<std::string, Channel *> user_chans = user->getJoined();
			for (std::map<std::string, Channel *>::iterator user_chans_it = user_chans.begin(); user_chans_it != user_chans.end(); user_chans_it++) {
				if (it->second->getJoined().count(user_chans_it->first)) {
					Channel *chan = it->second->getJoined().find(user_chans_it->first)->second;
					if (chan->isOp(it->second))
						rpl = chan->getName() + " " + it->second->getUserName() + " " + it->second->getHostName() + " irc.serverv " + it->second->getNick() + " H@ :0 " + it->second->getRealName();
					else
						rpl = chan->getName() + " " + it->second->getUserName() + " " + it->second->getHostName() + " irc.serverv " + it->second->getNick() + " H :0 " + it->second->getRealName();
					_sendExecuted(user, RPL_WHOREPLY(user->getClient(), user->getNick(), rpl));
					sent = true;
					rpl.clear();
				}
			}
			if (!it->second->isInvisible() && !sent) {
				rpl = "* " + it->second->getUserName() + " " + it->second->getHostName() + " irc.serverv " + it->second->getNick() + " H :0 " + it->second->getRealName();
				_sendExecuted(user, RPL_WHOREPLY(user->getClient(), user->getNick(), rpl));
				rpl.clear();
			}
			break;
		}
	}
	return _sendExecuted(user, RPL_ENDOFWHO(user->getClient(), user->getNick(), buff));
}
