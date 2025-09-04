#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"

const std::string Server::getChannelName(const std::string &line) const {
	std::cout << line << std::endl;
	const size_t channelPos = line.find('#');
	if (channelPos == std::string::npos) {
		return (" ");
	}

	const std::string tmp = line.substr(channelPos, line.length());

	const std::string channelName = tmp.substr(1, tmp.find(' '));

	return (channelName);
}

const std::string Server::getUserToKick(const std::string &line) const {
	const size_t channelPos = line.find('#');
	if (channelPos == std::string::npos)
		return "";

	const std::string tmp = line.substr(channelPos);

	size_t skipChannel = tmp.find(' ');
	if (skipChannel == std::string::npos)
		return "";

	size_t userStart = skipChannel + 1;

	size_t userEnd = tmp.find(' ', userStart);
	if (userEnd == std::string::npos)
		userEnd = tmp.length();

	const std::string user = tmp.substr(userStart, userEnd - userStart);
	return (user);
}

void Server::handleKick(int clientFd, const std::string &line) {
	std::string channelName = getChannelName(line);
	std::string kick = getUserToKick(line);
	const int kickId = findIdByName(kick);

	if (kickId == -1) {
		sendError(clientFd, ERR_INVALIDUSERNAME, "user does not exist");
		return ;
	}

	std::cout << channelName << std::endl;
	std::cout << kick << std::endl;

	if (kick.empty()) {
		sendError(clientFd, ERR_NEEDMOREPARAMS, "no param given to kick");
		return ;
	}

	else {
		for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it) {
			if (it->getName() == channelName) {
				std::cout << "TESTTEST" << std::endl;
				std::cout << it->hasPerm(clientFd) << std::endl;
				std::cout << it->isMember(kickId) << std::endl;
				if (!it->hasPerm(clientFd)) {
					std::cout << "NO PERM" << std::endl;
					sendError(clientFd, ERR_NOPERMFORHOST, "no perm on this channel");
					return ;
				} else if (!it->isMember(kickId)) {
					std::cout << "NOT MEMBER" << std::endl;
					sendError(clientFd, ERR_USERNOTINCHANNEL, "user not in this channel");
					return ;
				} else {
					std::cout << kick << " VA ETRE KICK DE " << channelName << " SON FD EST" << kickId << std::endl;
					it->removeMember(kickId);
					return ;
				}
			}
		}
	}
	std::cout << "NULLLLL" << std::endl;
}
