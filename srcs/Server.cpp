/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:12 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/21 16:08:28 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

bool Server::running = true;

Server::Server() {}
Server::Server(const Server &src) {*this = src;}
Server	Server::operator=(const Server &src) {
	this->port = src.port;
	this->password = src.password;
	return (*this);
}

Server::~Server() {
	close(this->socketfd);
	close(this->epollFd);
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
				this->handleInput(i);
			}
		}
	}
}

void Server::acceptUser() {
	int UserFd = accept(this->socketfd, NULL, NULL);
	if (UserFd < 0) {
		std::cerr << "Failed to accept User" << std::endl;
		return ;
	}

	epoll_event UserEvent;
	UserEvent.events = EPOLLIN;
	UserEvent.data.fd = UserFd;
	if (epoll_ctl(this->epollFd, EPOLL_CTL_ADD, UserFd, &UserEvent)) {
		throw(std::runtime_error("Error while adding User to epoll instance"));
	}

	User newUser;
	newUser.setFd(UserFd);
	this->Users.push_back(newUser);

	std::cout << "New User on fd : " << UserFd << std::endl;
}

void Server::handleInput(int i) {
	
}
