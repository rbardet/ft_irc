#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"

void Server::handleJoin(const int &clientFd, const std::string &line)
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

	broadcastJoinToChannel(channelName, clientFd);
	sendNamesList(clientFd, channelName);
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
			this->sendTopic(userFd, *it);
			break;
		}
	}
}





void Server::broadcastJoinToChannel(const std::string &channelName, int clientFd) const
{
	std::string nick = findNameById(clientFd);
	std::string user = Users.at(clientFd).getUsername();
	std::string host = "localhost";

	// pour que irssi sache (RFC format)
	std::string joinMsg = ":" + nick + "!" + user + "@" + host + " JOIN :" + channelName + "\r\n";

	// dire à TOUS les membres du canal
	for (std::vector<Channel>::const_iterator it = channelList.begin(); it != channelList.end(); ++it)
	{
		if (it->getName() == channelName)
		{
			std::vector<int> members = it->getAllMembers();
			for (size_t i = 0; i < members.size(); ++i)
				send(members[i], joinMsg.c_str(), joinMsg.size(), 0);
			break;
		}
	}
}

void Server::sendNamesList(int clientFd, const std::string &channelName) const
{
	//dire la list des membre a irssi
	std::string nick = findNameById(clientFd);
	std::string namesList = ":server " + std::string(RPL_NAMREPLY) + " " + nick + " = " + channelName + " :";

	for (std::vector<Channel>::const_iterator it = channelList.begin(); it != channelList.end(); ++it)
	{
		if (it->getName() == channelName)
		{
			std::vector<int> members = it->getAllMembers();
			for (size_t i = 0; i < members.size(); ++i)
			{
				if (i > 0) namesList += " ";
				if (it->isOperator(members[i])) namesList += "@";
				namesList += findNameById(members[i]);
			}
			break;
		}
	}
	namesList += "\r\n";
	send(clientFd, namesList.c_str(), namesList.size(), 0);

	std::string endNames = ":server " + std::string(RPL_ENDOFNAMES) + " " + nick + " " + channelName + " :End of /NAMES list\r\n";
	send(clientFd, endNames.c_str(), endNames.size(), 0);
}


