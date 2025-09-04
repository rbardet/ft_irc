/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:12 by rbardet-          #+#    #+#             */
/*   Updated: 2025/09/04 16:54:06 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Utils.hpp"

bool Server::running = true;

Server::Server() : socketfd(0), epollFd(0) {}
Server::Server(const Server &src) {*this = src;}
Server	Server::operator=(const Server &src) {
	this->port = src.port;
	this->password = src.password;
	return (*this);
}

Server::~Server() {
	if (this->socketfd > 0) {
		close(this->socketfd);
	}
	if (this->epollFd > 0) {
		close(this->epollFd);
	}
	for (std::map<int, User>::iterator it = Users.begin(); it != Users.end(); ++it) {
		it->second.closeConnection();
	}
}

void Server::signalHandler(int signum) {
	(void) signum;
	std::cout << std::endl << "Closing server..." << std::endl;
	running = false;
}

void Server::initSocket() {
	this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketfd < 0) {
		throw(std::runtime_error("Error while opening the socket"));
	}

	struct sockaddr_in servAddress;
	servAddress.sin_family = AF_INET;
	servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddress.sin_port = htons(this->port);

	if (bind(this->socketfd, (struct sockaddr *) &servAddress, sizeof(servAddress)) < 0) {
		throw(std::runtime_error("Error while binding address"));
	}

	if (listen(this->socketfd, MAX_USER) < 0) {
		throw(std::runtime_error("Error while opening the server"));
	}

}

void Server::initEpoll() {
	this->epollFd = epoll_create1(0);
	if (this->epollFd < 0) {
		throw(std::runtime_error("Error while creating epoll fd"));
	}

	this->event.events = EPOLLIN;
	this->event.data.fd = this->socketfd;
	if (epoll_ctl(this->epollFd, EPOLL_CTL_ADD, this->socketfd, &this->event)) {
		throw(std::runtime_error("Error while adding server to epoll instance"));
	}

	std::cout << "Server listening on port : " << this->port << std::endl;
}

void Server::initServer(const int &port, const std::string &password) {
	this->port = port;
	this->password = password;
	this->initSocket();
	this->initEpoll();
}

void Server::runServer() {
	while (running) {
		int eventNumber = epoll_wait(this->epollFd, this->events, MAX_EVENTS, -1);
		if (eventNumber == -1) {
			std::cerr << "Failed to get events" << std::endl;
			continue ;
		}

		for (int i = 0; i < eventNumber; i++) {
			if (events[i].data.fd == this->socketfd) {
				this->acceptUser();
			} else {
				this->parseInput(events[i].data.fd);
			}
		}
	}
}

void Server::handleCapReq(const int &userFd) const {
	std::string msg = ":server CAP * LS :multi-prefix sasl\r\n";
	send(userFd, msg.c_str(), msg.length(), 0);
}

void Server::acceptUser() {
	int userFd = accept(this->socketfd, NULL, NULL);
	if (userFd < 0) {
		std::cerr << "Failed to accept User" << std::endl;
		return ;
	}

	fcntl(userFd, F_SETFL, O_NONBLOCK);

	epoll_event UserEvent;
	UserEvent.events = EPOLLIN;
	UserEvent.data.fd = userFd;
	if (epoll_ctl(this->epollFd, EPOLL_CTL_ADD, userFd, &UserEvent)) {
		std::cerr << "Error while adding User to epoll instance";
		return ;
	}

	User newUser;
	newUser.setFd(userFd);
	this->Users.insert(std::pair<int, User>(userFd, newUser));

	handleCapReq(userFd);
	std::cout << "New User on fd : " << userFd << std::endl;
}

void Server::parseInput(int clientFd) {
	char input[BUFFER_SIZE];

	int inputLength = read(clientFd, input, sizeof(input) - 1);
	if (inputLength < 0) {
		std::cerr << "Error while reading client input from fd : " << clientFd << std::endl;
		return;
	} else if (inputLength == 0) {
		close(clientFd);
		this->Users.erase(clientFd);
		std::cout << "Closing connection on fd : " << clientFd << std::endl;
		return;
	}

	input[inputLength] = '\0';

	std::string &tmp = this->Users[clientFd].getInput();
	tmp.append(input, inputLength);

	size_t pos;
	while ((pos = tmp.find("\r\n")) != std::string::npos) {
		std::string line = tmp.substr(0, pos);
		tmp.erase(0, pos + 2);
		std::cout << "LINE: " << line << std::endl;

		handleLine(clientFd, line);
	}
}

void Server::handleLine(int clientFd, const std::string &line) {
	if (line.find("CAP REQ", 0) == 0) {
		handleCapReq(clientFd);
	}
	else if (line.find("NICK", 0) == 0) {
		handleNick(clientFd, line);
	} else if (line.find("USERNAME", 0) == 0) {
		handleUsername(clientFd, line);
	}
	else if (line.find("JOIN", 0) == 0) {
		handleJoin(clientFd, line);
	}
	else if (line.find("PRIVMSG", 0) == 0) {
		handleChannelMessage(clientFd, line);
	}
	else if (line.rfind("MODE", 0) == 0) {
		handleMode(clientFd, line);
	}
}


void Server::handleMode(int clientFd, const std::string &line) 
{

	
	char mode = line.find(MODE_CMD) + 1;
	std::cout << mode;


	switch (mode)
	{
		case 'i': 

		case 't':


		case 'k':


		case 'o':


		case 'l':

		default:
			std::string error = ":server " + ERR_UNKNOWNMODE + " :" + mode + " :No such mode\r\n";
			send(clientFd, error.c_str(), error.length(), 0);

	}
	
}

bool Server::nickAlreadyInUse(const std::string &nick) {
	for (std::map<int, User>::iterator it = this->Users.begin(); it != this->Users.end(); ++it) {
		if (it->second.getNickname() == nick) {
			return (true);
		}
	}
	return (false);
}

void Server::sendMessage(int &clientFd, int code, const std::string &message) const {
	const std::string buffer = ":server " + to_string(code) + " " + message + "\r\n";
	send(clientFd, buffer.c_str(), buffer.size(), 0);
}

void Server::handleNick(int clientFd, const std::string &line) {
	std::string nick = line.substr(NICK_CMD);
	if (nick.empty()) {
		sendMessage(clientFd, ERR_NONICKNAMEGIVEN, "no nickname given");
		return ;
	}

	if (this->nickAlreadyInUse(nick)) {
		sendMessage(clientFd, ERR_NICKCOLLISION, "this nick is already in use");
		return ;
	}

	this->Users[clientFd].setNickname(nick);
	std::string welcome  = ":server 001 :Welcome to the IRC server, " + nick + "\r\n";

	send(clientFd, welcome.c_str(), welcome.size(), 0);
}

void Server::handleUsername(int clientFd, const std::string &line) {
	std::string username = line.substr(USER_CMD);
	if (username.empty()) {
		sendMessage(clientFd, ERR_NEEDMOREPARAMS, "no username given");
		return ;
	}

	this->Users[clientFd].setUsername(username);
	std::string welcome  = ":server 001 :Welcome to the IRC server, " + username + "\r\n";

	send(clientFd, welcome.c_str(), welcome.size(), 0);
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

void Server::handleJoin(int clientFd, const std::string &line)
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
			break;
		}
	}
}

void Server::handleChannelMessage(int clientFd, const std::string &line) {
	size_t firstSpace = line.find(' ');
	if (firstSpace == std::string::npos)
		return;

	size_t secondSpace = line.find(' ', firstSpace + 1);
	if (secondSpace == std::string::npos)
		return;

	std::string channelName = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
	std::string message = line.substr(secondSpace + 1);

	if (!message.empty() && message[0] == ':')
		message.erase(0, 1);

	if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
		return;

	broadcastToChannel(channelName, message, clientFd);
}

void Server::broadcastToChannel(const std::string &channelName, const std::string &message, int senderFd) {
	for (std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it) {
		if (it->getName() == channelName) {
			if (!it->isMember(senderFd)) {
				std::string error = ":server 404 " + channelName + " :Cannot send to channel\r\n";
				send(senderFd, error.c_str(), error.length(), 0);
				return;
			}

			std::string nick = this->Users[senderFd].getNickname();
			std::string full = ":" + nick + "!user@host PRIVMSG " + channelName + " :" + message + "\r\n";

			std::vector<int> members = it->getAllMembers();
			for (std::vector<int>::iterator m = members.begin(); m != members.end(); ++m) {
				if (*m == senderFd)
					continue;
				send(*m, full.c_str(), full.length(), 0);
			}
			return;
		}
	}
	std::string error = ":server 403 " + channelName + " :No such channel\r\n";
	send(senderFd, error.c_str(), error.length(), 0);
}
