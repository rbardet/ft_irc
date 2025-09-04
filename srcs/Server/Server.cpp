#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"

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
	if (line.find("NICK", 0) == 0) {
		handleNick(clientFd, line);
	} else if (line.find("USER", 0) == 0) {
		handleUsername(clientFd, line);
	}
	else if (line.find("JOIN", 0) == 0) {
		handleJoin(clientFd, line);
	} else if (line.find("KICK", 0) == 0) {
		handleKick(clientFd, line);
	}
	else if (line.find("PRIVMSG", 0) == 0) {
		handleChannelMessage(clientFd, line);
	}
	else if (line.rfind("MODE", 0) == 0) {
		handleMode(clientFd, line);
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

void Server::sendError(const int &clientFd, const std::string code, const std::string &message) const {
	const std::string buffer = ":server " + code + " " + message + "\r\n";
	send(clientFd, buffer.c_str(), buffer.size(), 0);
}

void Server::sendRPL(const int &clientFd, std::string code, const std::string &nick, const std::string &message) const {
	std::string buffer = ":server " + code + " " + nick + " :" + message + "\r\n";
	std::cout << buffer << std::endl;
	send(clientFd, buffer.c_str(), buffer.size(), 0);
}

void Server::welcomeUser(const int &clientFd, const std::string &name) const {
	sendRPL(clientFd, RPL_WELCOME, name, "Welcome to the IRC server " + name + "!");
	sendRPL(clientFd, RPL_YOURHOST, name, "Your host is ircserv");
	sendRPL(clientFd, RPL_CREATED, name, "This server was created today");
}

void Server::handleNick(int clientFd, const std::string &line) {
	std::string nick = getParam(NICK_CMD, line);

	if (nick.empty()) {
		sendError(clientFd, ERR_NONICKNAMEGIVEN, "no nickname given");
		return ;
	}

	if (this->nickAlreadyInUse(nick)) {
		sendError(clientFd, ERR_NICKCOLLISION, "this nick is already in use");
		return ;
	}

	this->Users[clientFd].setNickname(nick);

	welcomeUser(clientFd, nick);
}

void Server::handleUsername(int clientFd, const std::string &line) {
	std::string username = getParam(USER_CMD, line);

	if (username.empty()) {
		sendError(clientFd, ERR_NEEDMOREPARAMS, "no username given");
		return ;
	}

	this->Users[clientFd].setUsername(username);

	welcomeUser(clientFd, username);
}

void Server::handleKick(int clientFd, const std::string &line) {
	(void)clientFd;
	(void)line;
	return ;
	// std::string kick = getParam(KICK_CMD, line);

	// if (kick.empty()) {
	// 	sendError(clientFd, ERR_NEEDMOREPARAMS, "no param given to kick");
	// 	return ;
	// } else {
	// 	if (this->channelList.hasPerm(clientFd)) {
	// 		/* code */
	// 	}

	// }
}

