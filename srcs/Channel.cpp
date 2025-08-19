/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:45:54 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/19 17:18:39 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel() {}
Channel::Channel(const Channel &src) {*this = src;}
Channel Channel::operator=(const Channel &src) {
	this->name = src.name;
	return(*this);
}
Channel::~Channel() {}

Channel::Channel(const std::string &name) {
	this->name = name;
}
