#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"

std::string getFilename(const std::string &message) {
	std::istringstream iss(message);
	std::string	dcc;
	std::string	send;
	std::string	filename;

	iss >> dcc >> send >> filename;

	if (dcc == CMD_DCC && (send == DCC_MODE_SEND || send == DCC_MODE_GET)) {
		return filename;
	}
	return (EMPTY_STRING);
}

void Server::handleDCC(const int &clientFd, const std::string &targetNick, const std::string &message) {
	const std::string mode = getParam(DCC_CMD_LENGTH, message);

	std::cout << "MODE DE DCC:" << std::endl;
	if (mode.empty()) {
		sendERR_NEEDMOREPARAMS(clientFd, CMD_DCC);
		return ;
	}

	const std::string filename(message);
	if (filename.empty()) {
		sendERR_NEEDMOREPARAMS(clientFd, CMD_DCC);
	}

	std::cout << "NOM DU FICHIER" << filename << std::endl;
	if (mode == DCC_MODE_SEND) {
		sendFile(clientFd, targetNick, message, filename);
	} else if (mode == DCC_MODE_GET) {
		getFile(clientFd, targetNick, message, filename);
	}
}

void Server::sendFile(const int &clientFd, const std::string &targetNick, const std::string &message, const std::string &filename) {
	(void)clientFd;
	(void)targetNick;
	(void)message;
	(void)filename;
}

void Server::getFile(const int &clientFd, const std::string &targetNick, const std::string &message, const std::string &filename) {
	(void)clientFd;
	(void)targetNick;
	(void)message;
	(void)filename;
}
