
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <netdb.h>
#include <csignal>
#include <fcntl.h>
#include <cerrno>
#include <map>
#include <vector>
#include <utility>
#include <poll.h>
#include <algorithm>
#include "Messages.hpp"
#include "Exception.hpp"
#include "Channel.hpp"
#include "User.hpp"

class Server;
class Channel;
class User;

typedef int (Server::*cmds)(User*, std::string);

class Server {
	private:
		std::string				_creation_time;
		std::string				_password;
		char					*_port;
		int						_sd;
		std::map<int, User*>	_users;
		std::vector<pollfd>		_pfds;
		int						_fd_count;
		std::string				_op_name;
		std::string				_op_password;
		std::string				_new_connection;
		std::vector<std::pair<std::string, std::string> >	_recvs;
		std::map<std::string, Channel *>					_channels;
		std::map<const std::string, cmds>					_cmds;
		std::map<int, std::string>							_client_buffers;

	public:
		Server(char *port, char *password);
		~Server();
		void	setup();
		void	launch();
		void	clear();

	private:
		void	_initCmd();
		void	_acceptUser();
		int		_manageRequest(pollfd pfds);
		//int		_fillRecvs(int fd);
		int		_fillRecvs(std::string);
		int		_manageCmd(pollfd pfd, std::pair<std::string, std::string> cmd);
		int		_sendAll(int fd, const char *buf, size_t len, int flags);
		int		_recvAll(pollfd pfd);
		std::pair<std::string, std::string>	_strToPair(std::string buff);
		std::pair<std::string, std::string>	_splitPrivMsg(std::string buff);
		std::string _getReason(std::string &buff);
		int		_sendError(User *user, std::string msg);
		int		_sendExecuted(User *user, std::string ret);
		int		_disconnectUser(User *user, int ret);
		int		_acceptConnection(User *user, std::pair<std::string, std::string> cmd);
		int		_registrationCompleted(User *user);
		bool	_validChars(std::string s);
		bool	_nickAlreadyUsed(User *current, std::string s);
		void	_sendJoinMsg(User *user, Channel *chan);
		void	_sendPrivMsg(User *sender, User *tagret, std::string chan_name, std::string msg, std::string cmd_type);
		void	_sendPartMsg(User *sender, std::map<std::string, User *> targets, std::string chan_name, std::string msg);
		void	_updateNickOnChans(std::string old_nick, User *user);
		void	_delEmptyChans();
		int		_checkModes(User *user, Channel *chan, std::string key);
		int		_applyMode(User *user, std::string mode, bool value);
		int		_applyMode(User *user, Channel *channel, std::string buff, bool value);
		int		_pass(User *user, std::string args);
		int		_user(User *user, std::string args);
		int		_nick(User *user, std::string buff);
		int		_pong(User *user, std::string buff);
		int		_quit(User *user, std::string args);
		int		_mode(User *user, std::string buff);
		int		_join(User *user, std::string buff);
		int		_part(User *user, std::string buff);
		int		_privmsg(User *user, std::string buff);
		int		_notice(User *user, std::string buff);
		int		_whois(User *user, std::string buff);
		int		_who(User *user, std::string buff);
		int		_kick(User *user, std::string buff);
		int		_invite(User *user, std::string buff);
		int		_topic(User *user, std::string buff);
		int		_oper(User *user, std::string buff);
		int		_die(User *user, std::string buff);
		int		_kill(User *user, std::string buff);
};

std::string currentTime();
