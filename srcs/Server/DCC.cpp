#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"

void Server::handleDCC(const int &clientFd, const std::string &targetNick, const std::string &message) {
	const std::string mode = getParam(DCC_CMD_LENGTH, message);

	if (mode.empty()) {
		sendERR_NEEDMOREPARAMS(clientFd, CMD_DCC);
		return ;
	}

	if (mode == "SEND") {
		sendFile(clientFd, targetNick, message);
	} else if (mode == "GET") {
		getFile(clientFd, targetNick, message);
	}

}

void Server::sendFile(const int &clientFd, const std::string &targetNick, const std::string &message) {
	(void)clientFd;
	(void)targetNick;
	(void)message;
}

void Server::getFile(const int &clientFd, const std::string &targetNick, const std::string &message) {
	(void)clientFd;
	(void)targetNick;
	(void)message;
}
