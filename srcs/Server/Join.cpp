#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"


void Server::handleJoin(const int &clientFd, const std::string &line)
{
	std::vector<std::string> channelName_andkey = parseJoinChannelName(line);

	if (channelName_andkey[0].empty()) 
	{
		std::cout << "Invalid JOIN command received from user " << clientFd << std::endl;
		return;
	}

	if (channelExists(channelName_andkey[0])) 
	{
		if (joinExistingChannel(channelName_andkey[0], channelName_andkey[1], clientFd)) 
		{
			std::cout << "User " << clientFd << " joined existing channel: " << channelName_andkey[0] << std::endl;
			broadcastJoinToChannel(channelName_andkey[0], clientFd);
			sendNamesList(clientFd, channelName_andkey[0]);
		}
	}
	else 
	{
		createChannel(channelName_andkey[0], clientFd);
		std::cout << "New channel created: " << channelName_andkey[0] << " by user " << clientFd << std::endl;
		broadcastJoinToChannel(channelName_andkey[0], clientFd);
		sendNamesList(clientFd, channelName_andkey[0]);
	}
}


std::vector<std::string> Server::parseJoinChannelName(const std::string &line)
{
    std::vector<std::string> channelName_andkey;

    // Format attendu: JOIN #channelname ou avec &
    size_t spacePos = line.find(' ');

    if (spacePos == std::string::npos)
        return channelName_andkey;

    // Resize sinon segfault
    channelName_andkey.resize(2);

    channelName_andkey[0] = line.substr(spacePos + 1);

    size_t space_after_channelName = line.find(' ', spacePos + 1);
    if (space_after_channelName == std::string::npos)
        return channelName_andkey;

    std::string key;

    if (space_after_channelName != std::string::npos)
        key = line.substr(space_after_channelName + 1); 

    // Le nom du canal est tout ce qui est avant l'espace
    channelName_andkey[0] = line.substr(spacePos + 1, space_after_channelName - spacePos - 1);

    // Si une clé est présente, on la stocke
    channelName_andkey[1] = key;

    return channelName_andkey;
}



bool Server::channelExists(const std::string &channelName) 
{
	for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it) 
	{
		if (it->getName() == channelName)
			return (true);
	}
	return (false);
}

void Server::createChannel(const std::string &channelName, int creatorFd) 
{
	channelList.push_back(Channel(channelName, creatorFd));
}

void Server::sendChannelError(const int &clientFd, const std::string &code, const std::string &nick, const std::string &channel, const std::string &message) const 
{
	std::string buffer = ":server " + code + " " + nick + " " + channel + " :" + message + "\r\n";
	send(clientFd, buffer.c_str(), buffer.size(), 0);
}

bool Server::joinExistingChannel(const std::string &channelName,  const std::string &key, int userFd) 
{
	for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it) 
	{
		if (it->getName() == channelName) 
		{
			std::string reason;
			if (!it->canJoin(userFd, key, reason)) 
			{
				if (reason.find("limit") != std::string::npos) 
				{
					sendChannelError(userFd, ERR_CHANNELISFULL, findNameById(userFd), channelName, "Cannot join channel (+l)");
				} 
				else if (reason.find("invited") != std::string::npos)
				{
					sendChannelError(userFd, ERR_INVITEONLYCHAN, findNameById(userFd), channelName, "Cannot join channel (+i)");
				} 
				else if (reason.find("password") != std::string::npos)
				{
					sendChannelError(userFd, ERR_BADCHANNELKEY, findNameById(userFd), channelName, "Cannot join channel (+k)");
				}
				return false;
			}
			it->addMember(userFd);
			return true;
		}
	}
	return false;
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


