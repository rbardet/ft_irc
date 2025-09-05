#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"

void Server::handleJoin(int clientFd, const std::string &line)
{
	std::string channelName = parseJoinChannelName(line);

	if (channelName.empty()) {
		std::cout << "Invalid JOIN command received from user " << clientFd << std::endl;
		return;
	}

	if (channelExists(channelName)) {
		joinExistingChannel(channelName, clientFd);
		std::cout << "User " << clientFd << " joined existing channel: " << channelName << std::endl;
	}
	else {
		createChannel(channelName, clientFd);
		std::cout << "New channel created: " << channelName << " by user " << clientFd << std::endl;
	}

	// broadcastJoinToChannel(channelName, clientFd);
	// sendNamesList(clientFd, channelName);
}

std::string Server::parseJoinChannelName(const std::string &line)
{
	// Format attendu: JOIN #channelname ou avec &
	size_t spacePos = line.find(' ');

	if (spacePos == std::string::npos)
		return "";

	std::string channelName = line.substr(spacePos + 1);

	// verif que commence par # ou &
	if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
		return "";

	return channelName;
}


bool Server::channelExists(const std::string &channelName) {
	for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it) {
		if (it->getName() == channelName)
			return (true);
	}
	return (false);
}

void Server::createChannel(const std::string &channelName, int creatorFd) {
	channelList.push_back(Channel(channelName, creatorFd));
}

void Server::joinExistingChannel(const std::string &channelName, int userFd) {
	for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it) {
		if (it->getName() == channelName) {
			it->addMember(userFd);
			break;
		}
	}
}
