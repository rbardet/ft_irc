#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"

const std::string Server::getTopic(const std::string &line) const {
	const size_t topicPos = line.find(':');
	if (topicPos == std::string::npos) {
		return (EMPTY_STRING);
	}

	const std::string topic = line.substr(topicPos + 1);

	return (topic);
}

void Server::handleTopic(const int &clientFd, const std::string &line) {
	const std::string topic = getTopic(line);
	const std::string channelName = getChannelName(line);

	std::cout << "TOPIC IS :" << topic << std::endl;
	std::cout << "CHANNELNAME IS :" << channelName<< std::endl;

	if (!this->channelExists(channelName)){
		sendRPL(clientFd, ERR_NOSUCHCHANNEL, this->Users[clientFd].getNickname(), channelName + MSG_ERR_NOSUCHCHANEL);
		return ;
	} else {
		for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it) {
			if (it->getName() == channelName) {
				if (topic.empty()) {
					sendTopic(clientFd, *it);
					return ;
				} else {
					if (!it->setTopic(clientFd, topic)) {
						sendRPL(clientFd, ERR_NOPERMFORHOST, this->Users[clientFd].getNickname(), MSG_ERR_NOPERMS);
					}
				}
			}
		}

	}
}

void Server::sendTopic(const int &clientFd, const Channel &channel) {
	if (channel.getTopic().empty()) {
		sendRPL(clientFd, RPL_NOTOPIC, this->Users[clientFd].getNickname(), channel.getName() + " :" + MSG_NEED_TOPIC);
	} else {
		sendRPL(clientFd, RPL_TOPIC, this->Users[clientFd].getNickname(), channel.getName() + " :" + channel.getTopic());
	}
}
