/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:13:27 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/19 14:45:40 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() {}
Client::Client(const Client &src) {*this = src;}
Client Client::operator=(const Client &src) {
	*this = src;
	return(*this);
}

Client::~Client() {}
Client::Client(const std::string &nickname, const std::string &username) {
	this->nickname = nickname;
	this->username = username;
}
