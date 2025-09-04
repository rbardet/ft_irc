#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"


void Server::handleChannelMessage(int clientFd, const std::string &line) {
	size_t idx_after_command = line.find(' ');
	if (idx_after_command == std::string::npos)
		return;

	size_t idx_after_channelName = line.find(' ', idx_after_command + 1);
	if (idx_after_channelName == std::string::npos)
		return;

	std::string channelName = line.substr(idx_after_command + 1, idx_after_channelName - idx_after_command - 1);
	std::string message = line.substr(idx_after_channelName + 1);

	if (!message.empty() && message[0] == ':')
		message.erase(0, 1);

	if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
		return;

	broadcastToChannel(channelName, message, clientFd);
}

void Server::broadcastToChannel(const std::string &channelName, const std::string &message, int senderFd)
{
	for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it)
	{
		if (it->getName() == channelName)
		{
			if (!it->isMember(senderFd))
			{
				sendError(senderFd, ERR_NOSUCHCHANNEL, "Cannot send to channel");
				return;
			}

			std::string nick = this->Users[senderFd].getNickname();
			std::string full = ":" + nick + "!user@host PRIVMSG " + channelName + " :" + message + "\r\n";

			std::vector<int> members = it->getAllMembers();
			for (std::vector<int>::iterator m = members.begin(); m != members.end(); ++m)
			{
				if (*m == senderFd)
					continue;
				send(*m, full.c_str(), full.length(), 0);
			}
			return;
		}
	}
	sendError(senderFd, ERR_NOSUCHCHANNEL, "No such channel");
}
