#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"
#include <stdlib.h>

void Server::handleMode(int clientFd, const std::string &line)
{
	size_t space_after_mode = line.find(' ');
	if (space_after_mode == std::string::npos)// npos = not found
		return;

	size_t space_after_channelName = line.find(' ', space_after_mode + 1);
	if (space_after_channelName == std::string::npos)
		return;

	std::string channelName = line.substr(space_after_mode + JUMP_TO_CHANNEL, space_after_channelName - space_after_mode - 1);
	std::string mode = line.substr(space_after_channelName + JUMP_TO_MODE, 2);

	if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
		return;

	std::string arg;

	if (line.length() <= space_after_channelName + JUMP_TO_ARG)
		arg = "";
	else
		arg = line.substr(space_after_channelName + JUMP_TO_ARG);

	if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
		return;

	if (!mode.empty() && (mode[0] == '+' || mode[0] == '-'))
		execMode(clientFd, channelName, mode, arg);
	else
		return;
}


// version clean qui marche pas

// void Server::handleMode(int clientFd, const std::string &line)
// {
//     size_t space_after_mode = line.find(' ');
//     if (space_after_mode == std::string::npos)
//         return;

//     size_t space_after_channelName = line.find(' ', space_after_mode + 1);
//     std::string channelName, mode, arg;

//     if (space_after_channelName != std::string::npos)
//         channelName = line.substr(space_after_mode + JUMP_TO_CHANNEL, space_after_channelName - space_after_mode - 1);
// 	else
//         channelName = line.substr(space_after_mode + JUMP_TO_MODE);

//     if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
//         return;


//     mode = line.substr(space_after_channelName + JUMP_TO_MODE, 1);

//     if (!mode.empty() && (mode[0] == '+' || mode[0] == '-'))
// 	{
//         size_t space_after_mode = line.find(' ', space_after_channelName + 1);
//         if (space_after_mode != std::string::npos)
//             arg = line.substr(space_after_mode + JUMP_TO_ARG);
//         execMode(clientFd, channelName, mode, arg);
//     }
// }


char Server::extractFlag(const std::string &mode)
{
	char mode_case = mode[MODE_FLAG];
	return (mode_case);
}

void Server::execMode(int clientFd, const std::string &channelName, const std::string &mode, std::string arg)
{
	char mode_case = extractFlag(mode);
	if (mode[0] == '+')
		setMode(clientFd, channelName, mode_case, true, arg);
	else
		setMode(clientFd, channelName, mode_case, false, arg);
}

void Server::noticeMode(const int &clientFd, const std::string &channelName, const char &mode, const bool status, const std::string &arg) {
	std::string flag;
	if (status) {
		flag += "+";
		flag += mode;
	} else {
		flag += "-";
		flag += mode;
	}

	std::string buffer(":");

	buffer += this->Users[clientFd].getNickname() + "!";
	buffer += this->Users[clientFd].getUsername() + "@";
	buffer += "localhost MODE ";
	buffer += channelName + " ";
	buffer += flag;
	if (!arg.empty()) {
		buffer += " " + arg;
	}
	buffer += "\r\n";

	std::cout << "MESSAGE DE MODE BROADCAST:" << buffer << std::endl;
	broadcastToAllMember(this->findChannelByName(channelName), buffer);
}

void Server::setMode(int clientFd, const std::string &channelName, char mode, bool set_or_unset, std::string arg)
{
	std::cout << "MODE TESTTTTTTTTTTTTTTTTTTTT" << std::endl;
	for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it)
	{
		if (it->getName() == channelName)
		{
			if (!it->isOperator(clientFd))
			{
				sendERR_CHANOPRIVSNEEDED(clientFd, channelName);
				return;
			}
			if (set_or_unset == true)
			{
				std::cout << "MODE +++++++" << std::endl;
				switch (mode)
				{
					case 'i':
						it->setInviteOnly(true);
						std::cout <<  "Invite is : " << it->getInviteOnly() << "\n";
						break;
					case 't':
						it->setTopicOpOnly(true);
						std::cout <<  "topicOpOnly is : " << it->getTopicOpOnly() << "\n";
						break;
					case 'k':
						it->setKey(arg);
						std::cout <<  "key is : " << it->getHasKey() << "\n";
						std::cout <<  "the key is : " << it->getKey() << "\n";
						break;
					case 'o':
						std::cout <<  arg << "\n";
						std::cout <<  findIdByName(arg) << "\n";
						std::cout <<  it->isMember(findIdByName(arg)) << "\n";
						it->addOperator(findIdByName(arg));
						std::cout << arg << " is operator ? : " << it->isOperator(findIdByName(arg)) << "\n";
						break;
					case 'l':
						if (arg.empty())
						{
							sendRPL(clientFd, ERR_NEEDMOREPARAMS, this->findNameById(clientFd), "MODE +l requires a limit argument");
							return;
						}
						it->setUserLimit(atoi(arg.c_str()));
						std::cout <<  "userLimit is : " << it->getUserLimit() << "\n";
						break;
					default:
						sendRPL(clientFd, ERR_UNKNOWNMODE, this->findNameById(clientFd), "No such mode");
				}
			}
			else {
				switch (mode)
				{
					std::cout << "MODE ------" << std::endl;
					case 'i':
						it->setInviteOnly(false);
						std::cout <<  "Invite is : " << it->getInviteOnly() << "\n";
						break;
					case 't':
						it->setTopicOpOnly(false);
						std::cout <<  "topicOnly is : " << it->getInviteOnly() << "\n";
						break;
					case 'k':
						it->clearKey();
						std::cout <<  "key is : " << it->getHasKey() << "\n";
						std::cout <<  "the key is : " << it->getKey() << "\n";
						break;
					case 'o':
						it->removeOperator(findIdByName(arg));
						std::cout << arg << " is operator ? : " << it->isOperator(findIdByName(arg)) << "\n";
						break;
					case 'l':
						it->setUserLimit(REMOVE_LIMIT);
						std::cout <<  "userLimit is : " << it->getUserLimit() << "\n";
						break;
					default:
						sendRPL(clientFd, ERR_UNKNOWNMODE, this->findNameById(clientFd), "No such mode");
				}
			}
			this->noticeMode(clientFd, channelName, mode, set_or_unset, arg);
		}
		return ;
	}
	std::cout << "CHANNEL EXISTE PAS" << std::endl;
	sendRPL(clientFd, ERR_NOSUCHCHANNEL, this->findNameById(clientFd), "No such channel");
}
