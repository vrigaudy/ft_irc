
#include "../../includes/Channel.hpp"

Channel::Channel(std::string name) : _name(name), _limited(false, size_t()),
_key(false, std::string()), _topic(false, std::string()), _public(true), _mode_t(false) {
}

Channel::~Channel(){
	_users.clear();
	_opers.clear();
}

std::string const &Channel::getName() const {
	return _name;
}

void Channel::addUser(User *user) {
	_users.insert(std::make_pair(user->getNick(), user));
	user->addChannel(this);
}

void Channel::removeUser(User *user) {
	if (user->isOp(this))
		user->removeOps(this);
	_users.erase(user->getNick());
	user->removeFromChannel(this);
}

void	Channel::removeByNick(std::string nick) {
	if (_users.count(nick))
		_users.erase(nick);
}

bool	Channel::isPublic() const {
	return	_public;
}

bool	Channel::isModet() const {
	return	_mode_t;
}

std::string	Channel::getUsersList() {
	std::string list;
	std::map<std::string, User *>::iterator it = _users.begin();

	for (; it != _users.end(); it++) {
		if (it != _users.begin())
			list += " ";
		if (isOp(it->second))
			list += "@";
		list += it->second->getNick();
	}
	return list;
}

std::string Channel::getModes() {
	std::string ret;
	
	if (!_public)
		ret += "i";
	if (_mode_t)
		ret += "t";
	if (_key.first)
		ret += "k";
	if (_limited.first)
		ret += "l";
	if (_key.first)
		ret += (" " + _key.second);
	if (_limited.first) {
		std::stringstream ss;
		ss << " " << _limited.second;
		ret += ss.str();
	}
	return ret;
}

bool Channel::isOp(User *user) {
	return _opers.count(user->getNick());
}

std::map<std::string, User *> Channel::getUsers() const {
	return _users;
}


std::map<std::string, User *> Channel::getOpers() const {
	return _opers;
}


std::pair<bool, size_t> Channel::getLimited() const {
	return _limited;
}

std::pair<bool, std::string> Channel::getKey() const {
	return _key;
}

std::pair<bool, std::string> Channel::getTopic() const {
	return _topic;
}

void Channel::addToOp(User *user) {
	_opers.insert(std::make_pair(user->getNick(), user));
	user->addOps(this);
}

void Channel::removeFromOp(User *user) {
	_opers.erase(user->getNick());
	user->removeOps(this);
}

void Channel::removeFromOpByNick(std::string nick) {
	if (_opers.count(nick))
		_opers.erase(nick);
}


void Channel::setLimited(bool value, size_t n) {
	_limited.first = value;
	_limited.second = n;
}

void Channel::setKey(bool value, std::string key) {
	_key.first = value;
	_key.second = key;
}

void Channel::setTopic(bool value, std::string topic) {
	_topic.first = value;
	_topic.second = topic;
}

void Channel::setPublic() {
	if (_public == true)
		_public = false;
	else
		_public = true;
}

void	Channel::setModet() {
	if (_mode_t == false)
		_mode_t = true;
	else
		_mode_t = false;
}
