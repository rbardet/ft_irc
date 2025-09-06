#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"

const std::string Server::getTopic(const std::string &line) const {
	const size_t topicPos = line.find(" :");
	if (topicPos == std::string::npos) {
		return (EMPTY_STRING);
	}

	const std::string topic = line.substr(topicPos + JUMP_TO_TOPIC);

	return (topic);
}

void Server::broadcastNewTopic(const std::string &topic, const std::string &channelName, const int &clientFd, Channel &channel) {
	const std::string nick = this->Users[clientFd].getNickname();
	const std::string user = this->Users[clientFd].getUsername();
	const std::string host = "localhost";
	const std::string msg = ":" + nick + "!" + user + "@" + host + " TOPIC " + channelName + " :" + topic + "\r\n";

	std::cout << "NOUVEAU TOPIC: " << topic << std::endl;
	broadcastToAllMember(channel, msg);
}

void Server::handleTopic(const int &clientFd, const std::string &line) 
{
	const std::string channelName = getChannelName(line);

	if (!this->channelExists(channelName))
	{
		sendRPL(clientFd, ERR_NOSUCHCHANNEL, this->Users[clientFd].getNickname(), channelName + MSG_ERR_NOSUCHCHANEL);
		return ;
	}

	const std::string topic = getTopic(line);

		for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it) {
			if (it->getName() == channelName) {
				if (topic.empty()) {
					sendTopic(clientFd, *it);
					return ;
				} else {
					if (!it->setTopic(clientFd, topic, this->Users[clientFd].getNickname())) {
						sendRPL(clientFd, ERR_NOPERMFORHOST, this->Users[clientFd].getNickname(), MSG_ERR_NOPERMS);
					} else {
						broadcastNewTopic(topic, channelName, clientFd, *it);
					}
					return ;
				}
			}
		}
}

void Server::sendTopic(const int &clientFd, const Channel &channel) {

	if (channel.getTopic().empty()) {
		this->sendRPL_NOTOPIC(clientFd, channel);
	} else {
		this->sendRPL_TOPIC(clientFd, channel);
		this->sendRPL_TOPICWHOTIME(clientFd, channel);
	}
}

void Server::sendRPL_NOTOPIC(const int &clientFd, const Channel &channel) {
	const std::string code = RPL_NOTOPIC;

	std::string buffer(SERV_NAME);
	buffer += code + " ";
	buffer += this->Users[clientFd].getUsername() + " ";
	buffer += channel.getName() + " :";
	buffer += MSG_NOTOPIC;
	buffer += "\r\n";

	send(clientFd, buffer.c_str(), buffer.size(), 0);
}

void Server::sendRPL_TOPIC(const int &clientFd, const Channel &channel) {
	const std::string code = RPL_TOPIC;

	std::string buffer(SERV_NAME);
	buffer += code + " ";
	buffer += this->Users[clientFd].getUsername() + " ";
	buffer += channel.getName() + " :";
	buffer += channel.getTopic() + "\r\n";

	send(clientFd, buffer.c_str(), buffer.size(), 0);
}

void Server::sendRPL_TOPICWHOTIME(const int &clientFd, const Channel &channel) {
	std::ostringstream oss;
	oss << channel.getTopicTime();
	const std::string code = RPL_TOPICWHOTIME;

	std::string buffer(SERV_NAME);
	buffer += code + " ";
	buffer += this->Users[clientFd].getNickname() + " ";
	buffer += channel.getName() + " ";
	buffer += channel.getTopicSetter() + " ";
	buffer += oss.str() + "\r\n";
	send(clientFd, buffer.c_str(), buffer.size(), 0);
}
