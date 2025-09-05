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

void Server::handleTopic(const int &clientFd, const std::string &line) {
	const std::string channelName = getChannelName(line);

	if (!this->channelExists(channelName)){
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

void Server::sendRPL_TOPICWHOTIME(const int &clientFd, const Channel &channel) {
	std::ostringstream oss;
	oss << channel.getTopicTime();
	const std::string code = RPL_TOPICWHOTIME;
	const std::string msg = ":server " + code + " " + this->Users[clientFd].getNickname() + " " + channel.getName() + " " + channel.getTopicSetter() + " " + oss.str();

	send(clientFd, msg.c_str(), msg.size(), 0);
}


void Server::sendTopic(const int &clientFd, const Channel &channel) {

	if (channel.getTopic().empty()) {
		sendRPL(clientFd, RPL_NOTOPIC, this->Users[clientFd].getNickname(), channel.getName() + " :" + MSG_NEED_TOPIC);
	} else {
		sendRPL(clientFd, RPL_TOPIC, this->Users[clientFd].getNickname(), channel.getName() + " :" + channel.getTopic());
		this->sendRPL_TOPICWHOTIME(clientFd, channel);
	}
}
