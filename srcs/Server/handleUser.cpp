#include "../../includes/Server.hpp"
#include "../../includes/Utils.hpp"

bool Server::nickAlreadyInUse(const std::string &nick) {
	for (std::map<int, User>::iterator it = this->Users.begin(); it != this->Users.end(); ++it) {
		if (it->second.getNickname() == nick) {
			return (true);
		}
	}
	return (false);
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

int Server::findIdByName(const std::string &name) {
	for (std::map<int, User>::iterator it = this->Users.begin(); it != this->Users.end(); ++it) {
		if (it->second.getNickname() == name) {
			return (it->first);
		}
	}
	return (-1);
}
