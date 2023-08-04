
#pragma once
#include <string>

#define BUFFER_SIZE 4096
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define UL "\033[4m"
#define TAB "\t"
#define SPACE "  "
#define ORANGE "\033[93m"
#define RED "\033[91m"
#define BLUE "\033[96m"
#define GREEN "\033[92m"
#define PINK "\033[95m"
#define STAR "\033[92m * \033[0m"

// REPLY

#define RPL_WELCOME(client, nickname) (":" + std::string(client) + " 001 " + std::string(nickname) + "\r\n")
#define RPL_YOURHOST(client, nickname) (":" + std::string(client) + " 002 " + std::string(nickname) + " :Your host is irc.server, running version 1.0\r\n")
#define RPL_CREATED(client, nickname, date) (":" + std::string(client) + " 003 " + std::string(nickname) + " :This server was created " + std::string(date) + "\r\n")
#define RPL_MYINFO(client, nickname) (":" + std::string(client) + " 004 " + std::string(nickname) + " irc.server 1.0 io kl\r\n")
#define RPL_PASS ": " GREEN "Connection accepted !\n" BOLD ORANGE "Welcome to our IRC server !\033[00m\r\n"
#define RPL_PASSSEND "Connection accepted: Password correct"
#define RPL_NICK(old_nick, nickname) (":" + std::string(old_nick) + " NICK " + std::string(nickname) + "\r\n")
#define RPL_QUIT(client, reason) (":" + std::string(client) + " QUIT :" + std::string(reason) + "\r\n")
#define RPL_JOIN(client, chan_name) (":" + std::string(client) + " JOIN :" + std::string(chan_name) + "\r\n")
#define RPL_UMODEIS(client, nickname, modes) (":" + std::string(client) + " 221 " + std::string(nickname) + " +" + modes + "\r\n")
#define RPL_WHOISUSER(client, nickuser, nickname, username, hostname, realname) (":" + std::string(client) + " 311 " + std::string(nickuser) + " " + std::string(nickname) + " " + std::string(username) + " " + std::string(hostname) + " * :" +std::string(realname) + "\r\n")
#define RPL_ENDOFWHO(client, nickname, mask) (":" + std::string(client) + " 315 " + std::string(nickname) + " " + std::string(mask) + " :End of /WHO list\r\n")
#define RPL_ENDOFWHOIS(client, nickname, target) (":" + std::string(client) + " 318 " + std::string(nickname) + " " + std::string(target) + " :End of /WHOIS list\r\n")
#define RPL_CHANNELMODEIS(client, nickname, chan_name, modes) (":" + std::string(client) + " 324 " + std::string(nickname) + " " + std::string(chan_name) + " +" + std::string(modes) + "\r\n")
#define RPL_CHANNELMODEIS2(client, nickname, chan_name, modes, target) (":" + std::string(client) + " 324 " + std::string(nickname) + " " + std::string(chan_name) + " +" + std::string(modes) + " " + std::string(target) + "\r\n")
#define RPL_NOTOPIC(client, nickname, chan_name) (":" + std::string(client) + " 331 " + std::string(nickname) + " " + std::string(chan_name) + " :No topic is set\r\n")
#define RPL_KICK(client, nickname, chan_name, to_kick, reason)(":" + std::string(client) + " KICK " + std::string(chan_name) + " " + std::string(to_kick) + " :" + std::string(reason) + "\r\n")
#define RPL_TOPIC(client, nickname, chan_name, topic) (":" + std::string(client) + " 332 " + std::string(nickname) + " " + std::string(chan_name) + " :" + std::string(topic) + "\r\n")
#define RPL_INVITE(client, invite_nick, chan_name) (":" + std::string(client) + " 341 " + "INVITE " + std::string(invite_nick) + " " + std::string(chan_name) + "\r\n")
#define RPL_WHOREPLY(client, nickname, msg) (":" + std::string(client) + " 352 " + std::string(nickname) + " " + std::string(msg) + "\r\n")
#define RPL_NAMEREPLY(client, nickname, chan_name, usernames) (":" + std::string(client) +" 353 " + std::string(nickname) + " = " + std::string(chan_name) + " :" + std::string(usernames) + "\r\n")
#define RPL_ENDOFNAMES(client, nickname, chan_name) (":" + std::string(client) +" 366 " + std::string(nickname) + " " + std::string(chan_name) + " :End of /NAMES list\r\n")
#define RPL_YOUREOPER(client, nickname) (":" + std::string(client) + " 381 " + std::string(nickname) + " :You are now an IRC Operator\r\n")
#define RPL_PARTMSG(client, nickname, chan_name, msg) (":" + std::string(client) + " PART " + std::string(chan_name) + " :" + msg + "\r\n")
#define RPL_PARTNOMSG(client, nickname, chan_name) (":" + std::string(client) + " PART " + std::string(chan_name) + " :" + "\r\n")

// ERROR

#define ERR_NOCAP ":irc.server 400 : " RED " Connection refused: No cap provided" RESET "\r\n"
#define ERR_NOPASS ":irc.server 400 : " RED " Connection refused: No password provided" RESET "\r\n"
#define ERR_NONICK ":irc.server 400 : " RED " Connection refused: No nickname provided, registration not completed" RESET "\r\n"
#define ERR_NOUSER ":irc.server 400 : " RED " Connection refused: No user informations provided, registration not completed" RESET "\r\n"
#define ERR_NOSUCHNICK(client, nickname, target) (":" + std::string(client) +  " 401 " + std::string(nickname) + RED " " + std::string(target) + RESET "\r\n")
#define ERR_NOSUCHCHANNEL(client, nickname, chan_name) (":" + std::string(client) + " 403 " + std::string(nickname) + RED + " " + std::string(chan_name) + " :No such channel" RESET "\r\n")
#define ERR_CANNOTSENDTOCHAN(client, nickname, target) (":" + std::string(client) + " 404 " RED + std::string(target) + " :Cannot send to channel" RESET "\r\n")
#define ERR_NORECIPIENT(client, nickname) (":" + std::string(client) + " 411 " + std::string(nickname) + RED " :No recipient given (PRIVMSG)" RESET "\r\n")
#define ERR_NOTEXTTOSEND(client, nickname) (":" + std::string(client) + " 412 " + std::string(nickname) + RED " :No text to send" RESET "\r\n")
#define ERR_UNKNOWNCOMMAND(client, nickname, cmd) (":" + std::string(client) +" 421 " + std::string(nickname) + RED + " " + std::string(cmd) + " :Unknown command" RESET "\r\n")
#define ERR_NONICKNAMEGIVEN(client, nickname) ":" + std::string(client) + " 431 " + std::string(nickname) + RED " NICK :No nickname provided" RESET "\r\n"
#define ERR_ERRONEUSNICKNAME(client, nickname) ":" + std::string(client) + " 432 " + std::string(nickname) + RED " NICK :Erroneus nickname" RESET "\r\n"
#define ERR_NICKNAMEINUSE(client, nickname) ":" + std::string(client) + " 433 " + std::string(nickname) + RED " NICK :Nickname is already in use" RESET "\r\n"
#define ERR_USERNOTINCHANNEL(client, nickname, target, channel) ":" + std::string(client) + " 441 " + std::string(nickname) + " " + std::string(target) + " " + std::string(channel) + RED " :They aren't on that channel" RESET "\r\n"
#define ERR_NOTONCHANNEL(client, nickname, chan_name) (":" + std::string(client) + " 442 " + std::string(nickname) + RED + " " + std::string(chan_name) + " :You're not on channel" RESET "\r\n"
#define ERR_USERONCHANNEL(client, nickname, invite_nick, chan_name) (":" + std::string(client) + " 443 " + std::string(nickname) + RED + " " + std::string(invite_nick) + " " + std::string(chan_name) + " :is already on channel" RESET "\r\n"
#define ERR_NEEDMOREPARAMS(client, nickname, cmd) (":" + std::string(client) + " 461 " + std::string(nickname) + RED + " " + std::string(cmd) + " :Not enough parameters" RESET "\r\n")
#define ERR_NOPREFIX(client, nickname, cmd) (":" + std::string(client) + " 461 " + std::string(nickname) + RED + " " + std::string(cmd) + " :No prefix before last param" RESET "\r\n")
#define ERR_ALREADYREGISTERED(client, nickname, cmd) ":" + std::string(client) + " 462 " + std::string(nickname) + RED " USER: You may not reregister" RESET "\r\n"
#define ERR_PASSWDMISMATCH(client, nickname) ":" + std::string(client) + " 464 " + std::string(nickname) + " " + RED " Connection refused: Password incorrect" RESET "\r\n"
#define ERR_KEYSET(client, nickname, channel) ":" + std::string(client) + " 467 " + std::string(nickname) + " " + std::string(channel) + RED " :Channel key already set" RESET "\r\n"
#define ERR_CHANNELISFULL(client, nickname, chan_name) (":" + std::string(client) + " 471 " + std::string(nickname) + " " + std::string(chan_name) + " :Cannot join channel (+l)" RESET "\r\n")
#define ERR_UNKNOWNMODE(client, nickname, mode, channel) ":" + std::string(client) + " 472 " + std::string(nickname) + " " + std::string(mode) + RED " :is unknown mode char to me for " + std::string(channel) + RESET "\r\n"
#define ERR_NOPRIVILEGES(client, nickname) (":" + std::string(client) + " 481 " + std::string(nickname) + RED + " :Permission Denied - You're not an IRC operator" RESET "\r\n")
#define ERR_CHANOPRIVSNEEDED(client, nickname, chan_name) (":" + std::string(client) + " 482 " + std::string(nickname) + RED + " " + std::string(chan_name) + " :You're not a channel operator" RESET "\r\n")
#define ERR_BADCHANNELKEY(client, nickname, chan_name) (":" + std::string(client) + " 475 " + std::string(nickname) + " " + std::string(chan_name) + " :Cannot join channel (+k)" RESET "\r\n")
#define ERR_UMODEUNKNOWNFLAG(client, nickname) (":" + std::string(client) + " 501 " + std::string(nickname) + RED " :Uknown MODE flag" RESET "\r\n")
#define ERR_USERSDONTMATCH(client, nickname) (":" + std::string(client) + " 502 "  + std::string(nickname) + RED " :Can't change mode for other users" RESET "\r\n")

// DISPLAY

#define DIS_CREATED(date) (ORANGE BOLD "[ircserv]" RESET BOLD " created " + std::string(date) + RESET)
#define DIS_WAITCONNEC ORANGE BOLD "[ircserv]" RESET BOLD " waiting for incoming connections... 😴" RESET
#define DIS_SERVSETTEDUP ORANGE BOLD "[ircserv]" GREEN " setted up on port "
#define DIS_EMOJICHECK " \033[32m\xE2\x9C\x93\033[0m" RESET
#define DIS_CONNECTED ORANGE BOLD "=========" GREEN "=========================\n" ORANGE BOLD "[ircserv]" GREEN " new incoming connection!\n" ORANGE BOLD "=========" GREEN "=========================" RESET
#define DIS_RECV BLUE BOLD "[ircserv]" RESET BLUE " Recv    <--    " BLUE BOLD "[Client "
#define DIS_RECVEND(cmd, args) ("]" RESET BLUE ":    " + std::string(cmd) + " " + std::string(args) + RESET)
#define DIS_ERR RED BOLD "[ircserv]" RESET RED " Send    -->    " RED BOLD "[Client "
#define DIS_ERREND(msg) ("]" RESET RED ":    " + std::string(msg) + RESET)
#define DIS_EXEC GREEN BOLD "[ircserv]" RESET GREEN " Send    -->    " GREEN BOLD "[Client "
#define DIS_EXECEND(msg) ("]" RESET GREEN ":    " + std::string(msg) + RESET)
