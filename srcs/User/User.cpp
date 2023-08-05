
#include "../../includes/User.hpp"

User::User(int sd) : _user_sd(sd), _auth(0), _tried_to_auth(0), _first_try(1),
_cap(0), _invisible(0), _op(0), _nick(), _user_name(), _real_name(), _host_name(), _invite_list() {
}

User::~User() {
}

int const &User::getUserSd() const {
	return _user_sd;
}

std::map<std::string, Channel *> User::getJoined() const {
	return _joined;
}

std::string const User::getClient() const {
	if (getFirstTry())
		return "";
	return (getNick() + "!" + getUserName() + "@" + getHostName());
}

std::string const User::getNick() const {
	if (_nick.empty())
		return "";
	return _nick;
}

std::string const &User::getUserName() const {
	return _user_name;
}

std::string const &User::getHostName() const {
	return _host_name;
}

std::string const &User::getRealName() const {
	return _real_name;
}

std::string User::getModes() {
	std::string ret = "";

	if (_invisible)
		ret += "i";
	if (_op)
		ret += "o";
	return ret;
}

bool const &User::getAuth() const {
	return _auth;
}

bool const &User::getTriedToAuth() const {
	return _tried_to_auth;
}

bool const &User::getFirstTry() const {
	return _first_try;
}

bool const &User::getCap() const {
	return _cap;
}

bool	User::getInvite(std::string chan) const {
	if (std::find(_invite_list.begin(), _invite_list.end(), chan) != _invite_list.end())
		return true;
	return false;
}

bool const &User::isOp() const {
	return _op;
}

bool const &User::isInvisible() const {
	return _invisible;
}

bool User::isOp(Channel *channel) {
	return _ops.count(channel->getName());
}

void User::setNick(std::string value) {
	_nick = std::string(value);
}

void User::setHostName(std::string value) {
	_host_name = std::string(value);
}

void User::setUserName(std::string value) {
	_user_name = std::string(value);
}

void User::setRealName(std::string value) {
	_real_name = std::string(value);
}

void User::setAuth(bool value) {
	_auth = value;
}

void User::setTriedToAuth(bool value) {
	_tried_to_auth = value;
}

void User::setFirstTry(bool value) {
	_first_try = value;
}

void User::setCap(bool value) {
	_cap = value;
}

void User::setOp(bool value) {
	_op = value;
}

void User::setInvisible(bool value) {
	_invisible = value;
}

void User::setInvite(std::string chan) {
	if (std::find(_invite_list.begin(), _invite_list.end(), chan) == _invite_list.end())
		_invite_list.push_back(chan);
}

void User::addChannel(Channel *channel) {
	_joined.insert(std::make_pair(channel->getName(), channel));
}

void User::addOps(Channel *channel) {
	_ops.insert(std::make_pair(channel->getName(), channel));
}

void User::removeFromChannel(Channel *channel) {
	_joined.erase(channel->getName());
}

void User::removeOps(Channel *channel) {
	_ops.erase(channel->getName());
}

void User::removeFromAll() {
	if (!_joined.size())
		return;

	std::vector<std::string> vec;
	for (std::map<std::string, Channel *>::iterator it = _joined.begin(); it != _joined.end(); it++)
		vec.push_back(it->first);
	for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++)
		_joined[*it]->removeUser(this);
}

