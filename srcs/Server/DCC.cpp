#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"

t_dcc Server::getDCCInfo(const std::string &message) {
	std::istringstream iss(message);
	t_dcc	dccData;

	iss >> dccData.dcc >> dccData.mode >> dccData.filename >> dccData.ip >> dccData.port >> dccData.fileSize;

	return(dccData);
}

bool Server::hasAllDCCData(const t_dcc &dccData) {
	if (dccData.dcc.empty() || dccData.mode.empty() || dccData.filename.empty() || dccData.ip.empty() ||
		dccData.port.empty() || dccData.fileSize.empty()) {
		return(false);
	}

	return (true);
}

void Server::handleDCC(const int &clientFd, const std::string &targetNick, const std::string &message) {
	const t_dcc dccData = getDCCInfo(message);

	if (!this->hasAllDCCData(dccData)) {
		sendERR_NEEDMOREPARAMS(clientFd, CMD_DCC);
		return ;
	}

	if (dccData.mode == DCC_MODE_SEND) {
		sendFile(clientFd, targetNick, message, dccData);
	} else if (dccData.mode == DCC_MODE_GET) {
		getFile(clientFd, targetNick, message, dccData);
	}
}

void Server::sendFile(const int &clientFd, const std::string &targetNick, const std::string &message, const t_dcc &dccData) {
	(void)clientFd;
	(void)targetNick;
	(void)message;
	(void)dccData;
}

void Server::getFile(const int &clientFd, const std::string &targetNick, const std::string &message, const t_dcc &dccData) {
	(void)clientFd;
	(void)targetNick;
	(void)message;
	(void)dccData;
}


int Server::initDccSocket(const int &port)
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
