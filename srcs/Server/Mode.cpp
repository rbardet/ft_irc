#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"
#include <stdlib.h>

void Server::handleMode(int clientFd, const std::string &line)
{
	size_t idx_after_mode = line.find(' ');
	if (idx_after_mode == std::string::npos)// npos = not found
		return;

	size_t idx_after_channelName = line.find(' ', idx_after_mode + 1);
	if (idx_after_channelName == std::string::npos)
		return;

	std::string channelName = line.substr(idx_after_mode + 1, idx_after_channelName - idx_after_mode - 1);
	std::string mode = line.substr(idx_after_channelName + 1, 2);
    if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
		return;
    std::string arg = line.substr(idx_after_channelName + 4);

    if (arg.empty())
    {
        arg = "";
    }

	if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
		return;

	if (!mode.empty() && (mode[0] == '+' || mode[0] == '-'))
		execMode(clientFd, channelName, mode, arg);
    else
        return;     
}

char Server::extractFlag(const std::string &mode)
{
	char mode_case = mode[MODE_CHAR];
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

void Server::setMode(int clientFd, const std::string &channelName, char mode, bool set_or_unset, std::string arg)
{
	for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it)
	{
		if (it->getName() == channelName)
		{
			if (!it->isOperator(clientFd))
			{
				sendRPL(clientFd, ERR_NOPRIVILEGES, this->findNameById(clientFd), "No operator privileges");
				return;
			}
			if (set_or_unset == true)
			{
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
						it->setUserLimit(atoi(arg.c_str()));
                        std::cout <<  "userLimit is : " << it->getUserLimit() << "\n";
						break;
					default:
						sendRPL(clientFd, ERR_UNKNOWNMODE, this->findNameById(clientFd), "No such mode");
				}
			}
			else
				switch (mode)
				{
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
	}
	sendRPL(clientFd, ERR_NOSUCHCHANNEL, this->findNameById(clientFd), "No such channel");
}
