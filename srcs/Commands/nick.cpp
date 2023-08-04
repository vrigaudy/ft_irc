
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"

void	Server::_updateNickOnChans(std::string old_nick, User *user) {
	std::map<std::string, Channel *> channels = user->getJoined();

	if (channels.size()) {
		for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++) {
			if (it->second->getUsers().count(old_nick)) {
				it->second->removeByNick(old_nick);
				it->second->addUser(user);
			}
			if (it->second->getOpers().count(old_nick)) {
				it->second->removeFromOpByNick(old_nick);
				it->second->addToOp(user);
			}
		}
	}
}

int	Server::_nick(User *user, std::string buff) {
	if (buff.empty())
		return _sendError(user, ERR_NONICKNAMEGIVEN(user->getClient(), user->getNick()));
	else if (!_validChars(buff))
		return _sendError(user, ERR_ERRONEUSNICKNAME(user->getClient(), user->getNick()));
	else if (_nickAlreadyUsed(user, buff)) {
		if (user->getFirstTry()) {
			user->setNick(buff);
			while (_nickAlreadyUsed(user, buff))
				buff.insert(buff.end(), '_');
		}
		else
			return _sendError(user, ERR_NICKNAMEINUSE(user->getClient(), user->getNick()));
	}
	std::string old_nick;
	if (user->getNick().empty())
		old_nick = buff;
	else
		old_nick = user->getNick();
	user->setNick(buff);
	_updateNickOnChans(old_nick, user);
	return _sendExecuted(user, RPL_NICK(old_nick, user->getNick()));
}
