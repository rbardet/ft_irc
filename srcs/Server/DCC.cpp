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


int Server::initDccSocket(int port)
{

	int dccfd = socket(AF_INET, SOCK_STREAM, 0);
	if (dccfd < 0) {
		throw(std::runtime_error("Error while opening the socket"));
	}

	struct sockaddr_in DccAdress;
	DccAdress.sin_family = AF_INET;
	DccAdress.sin_addr.s_addr = htonl(INADDR_ANY);
	DccAdress.sin_port = htons(port);


	if (bind(dccfd, (struct sockaddr *) &DccAdress, sizeof(DccAdress)) < 0) {
		throw(std::runtime_error("Error while binding address"));
	}

	if (listen(dccfd, MAX_USER) < 0) {
		throw(std::runtime_error("Error while opening the server"));
	}

	return (dccfd);
}