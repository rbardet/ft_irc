/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:45:54 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/19 18:42:15 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel() {}

Channel::Channel(std::string name, std::string admin)
{
	this->name = name;
	this->admin = admin;
}


Channel::Channel(const Channel &src) {*this = src;}
Channel Channel::operator=(const Channel &src) {
	this->name = src.name;
	return(*this);
}
Channel::~Channel() {}

Channel::Channel(const std::string &name) {
	this->name = name;
	this->invite_only = false;
}
