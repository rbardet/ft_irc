/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:13:27 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/21 15:54:31 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

User::User() : nickname(""), username(""), input(""), fd(0) {}
User::User(const User &src) {
	*this = src;
}
User &User::operator=(const User &src) {
	if (this == &src)
		return (*this);
	this->nickname = src.nickname;
	this->username = src.username;
	this->input = src.input;
	this->fd = src.fd;
	return (*this);
}
User::~User() {}

User::User(const std::string &nickname, const std::string &username) : nickname(nickname), username(username), input(""), fd(0) {}

void User::setFd(const int &fd) {
	this->fd = fd;
}

void User::setNickname(const std::string &nickname) {
	this->nickname = nickname;
}

void User::setUsername(const std::string &username) {
	this->username = username;
}

void User::closeConnection() {
	if (this->fd > 0) {
		close(this->fd);
	}
}

void User::tryRegisterUser() {
	if (getHasNickname() && getHasUsername() && getHasPass()) {
		this->isRegister = true;
	}
}
