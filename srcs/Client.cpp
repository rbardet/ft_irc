/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:13:27 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/21 15:54:31 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client() {}
Client::Client(const Client &src) {*this = src;}
Client Client::operator=(const Client &src) {
	this->nickname = src.nickname;
	this->username = src.username;
	return(*this);
}
Client::~Client() {}

Client::Client(const std::string &nickname, const std::string &username) {
	this->nickname = nickname;
	this->username = username;
}

void Client::setFd(const int &fd) {this->fd = fd;}
void Client::setNickname(const std::string &nickname) {this->nickname = nickname;}
void Client::setUsername(const std::string &username) {this->username = username;}
