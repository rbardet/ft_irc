/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:13:27 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/19 17:18:56 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

User::User() {}
User::User(const User &src) {*this = src;}
User User::operator=(const User &src) {
	this->nickname = src.nickname;
	this->username = src.username;
	return(*this);
}

User::~User() {}
User::User(const std::string &nickname, const std::string &username) {
	this->nickname = nickname;
	this->username = username;
}
