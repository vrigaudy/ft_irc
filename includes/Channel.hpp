
#pragma once

#include "Exception.hpp"
#include "Server.hpp"
#include "User.hpp"

class User;

class Channel {
	private:
		std::string						_name;
		std::pair<bool, size_t>			_limited;
		std::pair<bool, std::string>	_key;
		std::pair<bool, std::string>	_topic;
		std::map<std::string, User *>	_users;
		std::map<std::string, User *>	_opers;

	public:
		Channel(std::string name);
		~Channel();
		std::string const &getName() const;
		void addUser(User *user);
		void removeUser(User *user);
		void removeByNick(std::string nick);
		bool isOp(User *user);
		std::string getUsersList();
		std::string getModes();
		std::map<std::string, User *> getUsers() const;
		std::map<std::string, User *> getOpers() const;
		std::pair<bool, size_t> getLimited() const;
		std::pair<bool, std::string> getKey() const;
		std::pair<bool, std::string> getTopic() const;
		void addToOp(User *user);
		void removeFromOp(User *user);
		void removeFromOpByNick(std::string nick);
		void setLimited(bool value, size_t n);
		void setKey(bool value, std::string key);
		void setTopic(bool value, std::string topic);

};
