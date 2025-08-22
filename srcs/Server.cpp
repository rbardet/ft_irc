/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:12 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/22 17:02:31 by robin            ###   ########.fr       */
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
	for (size_t i = 0; i < this->Users.size(); i++) {
		this->Users[i].closeConnection();
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
				this->handleInput(events[i].data.fd);
			}
		}
	}
}

void Server::sendMessage(const int &userFd, const int &code) const {
	std::string message = " " + code;
	if (send(userFd, message.c_str(), message.length(), 0) == -1) {
		std::cerr << "Failed to send message";
	}
}

void Server::sendInitialCap(const int &userFd) const {
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

	sendInitialCap(userFd);
	std::cout << "New User on fd : " << userFd << std::endl;
}

std::vector<std::string> Server::parseInput(std::string &input) {
	std::vector<std::string> token;
	size_t	pos = 0;
	size_t	lastPos = 0;
	while (pos != std::string::npos) {
		pos = input.find("\r\n");
		if (pos == std::string::npos) {
			break ;
		}
		std::string tmp = input.substr(lastPos, pos);
		lastPos = pos + 2;
		token.push_back(tmp);
	}
	return (token);
}

void Server::handleInput(int clientFd) {
    char input[BUFFER_SIZE];

    int inputLength = read(clientFd, input, sizeof(input) - 1);
    if (inputLength < 0) {
        std::cerr << "Error while reading client input from fd : " << clientFd << std::endl;
        return ;
    } else if (inputLength == 0) {
        close(clientFd);
        this->Users.erase(clientFd);
        std::cout << "Closing connection on fd : " << clientFd << std::endl;
        return ;
    }

    input[inputLength] = '\0';
    // std::string tmp(input, inputLength);

    // std::vector<std::string> token = parseInput(tmp);
    // for (size_t i = 0; i < token.size(); i++) {
    //     std::cout << "TOKEN N" << i << ": " << token[i] << std::endl;
    // }
}

