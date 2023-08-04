
#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"

int	Server::_pass(User *user, std::string args) {
	user->setTriedToAuth(true);
	if (user->getAuth())
		return _sendError(user, ERR_ALREADYREGISTERED(user->getClient(), user->getNick(), "PASS"));
	if (args != _password)
		return _disconnectUser(user, 2);
	user->setAuth(true);
	std::string ok(RPL_PASS);
	_sendAll(user->getUserSd(), ok.c_str(), ok.length(), 0);
	std::cout << DIS_EXEC << user->getUserSd() << DIS_EXECEND(RPL_PASSSEND) << std::endl;
	return 0;
}
