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

void Server::handleNick(const int &clientFd, const std::string &line) {
	std::string nick = getParam(NICK_CMD_LENGTH, line);

	welcomeUser(clientFd, nick);
	this->Users[clientFd].hasWelcomeMessage();

	if (nick.empty()) {
		sendRPL(clientFd, ERR_NONICKNAMEGIVEN, this->findNameById(clientFd), MSG_ERR_NEEDMOREPARAMS);
		return ;
	}

	if (this->nickAlreadyInUse(nick)) {
		sendRPL(clientFd, ERR_NICKCOLLISION, this->findNameById(clientFd), MSG_ERR_NICKCOLLISION);
		return ;
	}

	this->Users[clientFd].setNickname(nick);

	this->Users[clientFd].setHasNickname();

	this->Users[clientFd].tryRegisterUser();
}

void Server::handleUsername(const int &clientFd, const std::string &line) {
	std::string username = getParam(USER_CMD_LENGTH, line);

	if (username.empty()) {
		sendRPL(clientFd, ERR_NEEDMOREPARAMS, this->findNameById(clientFd), MSG_ERR_NEEDMOREPARAMS);
		return ;
	}

	this->Users[clientFd].setHasUsername();

	this->Users[clientFd].setUsername(username);

	this->Users[clientFd].tryRegisterUser();
}

int Server::findIdByName(const std::string &name) {
	for (std::map<int, User>::iterator it = this->Users.begin(); it != this->Users.end(); ++it) {
		if (it->second.getNickname() == name) {
			return (it->first);
		}
	}
	return (-1);
}

std::string Server::findNameById(const int &clientFd) {
	for (std::map<int, User>::iterator it = this->Users.begin(); it != this->Users.end(); ++it) {
		if (it->second.getFd() == clientFd) {
			return (it->second.getNickname());
		}
	}
	return (" ");
}
