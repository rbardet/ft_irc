#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"
#include <fstream>

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
	t_dcc dccData = getDCCInfo(message);

	if (!this->hasAllDCCData(dccData)) {
		sendERR_NEEDMOREPARAMS(clientFd, CMD_DCC);
		return ;
	}

	if (dccData.mode == DCC_MODE_SEND) {
		sendFile(clientFd, targetNick, dccData);
	} else if (dccData.mode == DCC_MODE_GET) {
		getFile(clientFd, targetNick, dccData);
	}
}

void Server::sendFile(const int &clientFd, const std::string &targetNick, t_dcc &dccData) {
	(void)clientFd;
	(void)targetNick;
	int dccsocket = initDccSocket(std::atoi(dccData.port.c_str()));
	if (dccsocket < 0) {
		return ;
	}

	std::ifstream file(dccData.filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: cannot open " << dccData.filename << std::endl;
		close(dccsocket);
		return;
	}

	char	buffer[BUFFER_SIZE];
	while (!file.eof()) {
		file.read(buffer, sizeof(buffer));
		send(dccsocket, buffer, sizeof(buffer), 0);
	}
}

void Server::getFile(const int &clientFd, const std::string &targetNick, t_dcc &dccData) {
	(void)clientFd;
	(void)targetNick;
	(void)dccData;
}


int Server::initDccSocket(const int &port)
{
	int opt = 1;
	int dccfd = socket(AF_INET, SOCK_STREAM, 0);
	if (dccfd < 0) {
		std::cerr << "Error while setting option for socket" << std::endl;
		return(-1);
	}

	struct sockaddr_in DccAdress;
	DccAdress.sin_family = AF_INET;
	DccAdress.sin_addr.s_addr = htonl(INADDR_ANY);
	DccAdress.sin_port = htons(port);

	if (setsockopt(dccfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		close(dccfd);
		std::cerr << "Error while setting option for socket" << std::endl;
		return(-1);
	}

	if (bind(dccfd, (struct sockaddr *) &DccAdress, sizeof(DccAdress)) < 0) {
		close(dccfd);
		std::cerr << "Error while binding address" << std::endl;
		return(-1);
	}

	if (listen(dccfd, MAX_USER) < 0) {
		close(dccfd);
		std::cerr << "Error while binding address" << std::endl;
		return(-1);
	}

	return (dccfd);
}
