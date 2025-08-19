/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:12 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/19 18:18:50 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server() {}
Server::Server(const Server &src) {*this = src;}
Server	Server::operator=(const Server &src) {
	this->port = src.port;
	this->password = src.password;
	return (*this);
}

Server::~Server() {
	close(this->socketfd);
}

Server::Server(const int &port, const std::string &password) {
	this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketfd == -1) {
		throw(std::runtime_error("Error while opening the socket"));
	}
	this->port = port;
	this->password = password;
}
