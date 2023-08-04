
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"

int Server::_registrationCompleted(User *user) {
	_sendExecuted(user, RPL_WELCOME(user->getClient(), user->getNick()));
	_sendExecuted(user, RPL_YOURHOST(user->getClient(), user->getNick()));
	_sendExecuted(user, RPL_CREATED(user->getClient(), user->getNick(), _creation_time));
	_sendExecuted(user, RPL_MYINFO(user->getClient(), user->getNick()));
	return 0;
}

std::string currentTime() {
	time_t t = std::time(0);
	struct tm *now = std::localtime(&t);
	std::string time(asctime(now));
	time.erase(time.end() - 1);
	return time;
}

int Server::_sendError(User *user, std::string err) {
	_sendAll(user->getUserSd(), err.c_str(), err.length(), 0);
	std::cout << DIS_ERR << user->getUserSd() << DIS_ERREND(err);
	return 1;
}

int Server::_sendExecuted(User *user, std::string ret) {
	_sendAll(user->getUserSd(), ret.c_str(), ret.length(), 0);
	std::cout << DIS_EXEC << user->getUserSd() << DIS_EXECEND(ret);
	return 0;
}

bool	Server::_validChars(std::string s) {
	for(size_t i = 0; i < s.length(); i++)
		if (s[i] < 33 || s[i] > 126)
			return false;
	return true;
}

bool	Server::_nickAlreadyUsed(User *current, std::string s) {
	for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++)
		if (it->second->getNick() == s && it->second->getUserSd() != current->getUserSd())
			return true;
	return false;
}

int Server::_acceptConnection(User *user, std::pair<std::string, std::string> cmd) {
	if (!user->getCap() && cmd.first == "CAP" && cmd.second[0] == 'L' && cmd.second[1] == 'S')
		return user->setCap(true), 0;
	else if (!user->getTriedToAuth() && cmd.first == "PASS") {
		if (!user->getCap())
			return _disconnectUser(user, 2);
	}
	else if (user->getNick() == "" && cmd.first == "NICK") {
		if (!user->getAuth())
			return _disconnectUser(user, 2);
	}
	else if (cmd.first == "USER") {
		if (user->getNick() == "")
			return _disconnectUser(user, 2);
	}
	else
		return _disconnectUser(user, 2);
	return 0;
}

std::pair<std::string, std::string> Server::_strToPair(std::string buff) {
	size_t i = buff.find(':');
	if (i == buff.npos)
		return std::make_pair(buff, std::string(""));

	std::string first(buff.begin(), buff.begin() + i);
	std::string second(buff.begin() + i + 1, buff.end());

	i = first.find(' ');
	if (i != first.npos)
		first.erase(first.begin() + i, first.end());
	return std::make_pair(std::string(first), std::string(second));
}

void	Server::_delEmptyChans() {
	std::map<std::string, Channel *>::iterator it = _channels.begin();
	std::map<std::string, Channel *>::iterator to_del;
	for(; it != _channels.end();) {
		if (it->second->getUsers().empty()) {
			to_del = it;
			it++;
			delete to_del->second;
			_channels.erase(to_del);
		}
		else
			it++;
	}
}
