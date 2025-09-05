#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"

const std::string Server::getChannelName(const std::string &line) const {
	std::cout << line << std::endl;
	const size_t channelPos = line.find('#');
	if (channelPos == std::string::npos) {
		return (EMPTY_STRING);
	}

	const std::string tmp = line.substr(channelPos, line.length());

	const std::string channelName = tmp.substr(0, tmp.find(' '));

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

void Server::handleKick(const int &clientFd, const std::string &line) {
	std::string channelName = getChannelName(line);
	std::string kick = getUserToKick(line);
	const int kickId = findIdByName(kick);

	if (kickId == -1) {
		sendRPL(clientFd, ERR_INVALIDUSERNAME, this->Users[clientFd].getNickname(), MSG_ERR_WRONGUSER);
		return ;
	}

	std::cout << channelName << std::endl;
	std::cout << kick << std::endl;

	if (kick.empty()) {
		sendRPL(clientFd, ERR_NEEDMOREPARAMS, this->Users[clientFd].getNickname(), MSG_ERR_NEEDMOREPARAMS);
		return ;
	}

	else {
		for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it) {
			std::cout << it->getName() << std::endl;
			if (it->getName() == channelName) {
				if (!it->hasPerm(clientFd)) {
					sendRPL(clientFd, ERR_NOPERMFORHOST, this->Users[clientFd].getNickname(), MSG_ERR_NOPERMS);
					return ;
				} else if (!it->isMember(kickId)) {
					sendRPL(clientFd, ERR_USERNOTINCHANNEL, this->Users[clientFd].getNickname(), MSG_ERR_USERNOTINCHANNEL);
					return ;
				} else {
					std::string kicker = findNameById(clientFd);
					std::string reason = "Kicked by " + kicker;
					broadcastKickConfirmation(channelName, kicker, kick, reason);
					it->removeMember(kickId);
					return ;
				}
			}
		}
	}
}
