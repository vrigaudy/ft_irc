
#pragma once

#include "Server.hpp"

class Channel;

class User {
	private:
		int			_user_sd;
		bool		_auth;
		bool		_tried_to_auth;
		bool		_first_try;
		bool		_cap;
		bool		_invisible;
		bool		_op;
		std::string	_nick;
		std::string	_mode;
		std::string	_user_name;
		std::string	_real_name;
		std::string	_host_name;
		std::map<std::string, Channel *> _ops;
		std::map<std::string, Channel *> _joined;
		User();
		std::vector<std::string>	_invite_list;

	public:
		User(int sd);
		~User();
		std::map<std::string, Channel *> getJoined() const;
		int const			&getUserSd() const;
		std::string const	getClient() const;
		std::string const	getNick() const;
		std::string const	&getUserName() const;
		std::string const	&getHostName() const;
		std::string const	&getRealName() const;
		std::string			getModes();
		bool const			&getAuth() const;
		bool const			&getTriedToAuth() const;
		bool const			&getFirstTry() const;
		bool const			&getCap() const;
		bool const			&isOp() const;
		bool const			&isInvisible() const;
		bool				getInvite(std::string chan) const;
		bool				isOp(Channel *channel);
		void				setNick(std::string value);
		void				setUserName(std::string value);
		void				setHostName(std::string value);
		void				setRealName(std::string value);
		void				setAuth(bool value);
		void				setTriedToAuth(bool value);
		void				setFirstTry(bool value);
		void				setCap(bool value);
		void				setOp(bool value);
		void				setInvisible(bool value);
		void				setInvite(std::string chan);
		void				addChannel(Channel *channel);
		void				addOps(Channel *channel);
		void				removeFromChannel(Channel *channel);
		void				removeOps(Channel *channel);
		void				removeFromAll();
};
