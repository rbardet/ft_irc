/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:39:17 by rbardet-          #+#    #+#             */
/*   Updated: 2025/09/04 17:03:01 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>

#define PORT 1
#define PASSWORD 2

#define SERV_NAME "ircserv"

#define WE_CODE 001

#define MODE_CMD 5

#define ERR_UNKNOWNMODE 472
#define NICK_CMD 5
#define USER_CMD 5

#define REMOVE_LIMIT 0

#define ERR_NOSUCHCHANNEL 403
#define ERR_CANNOTSENDTOCHAN 404
#define ERR_NONICKNAMEGIVEN 431
#define ERR_NICKCOLLISION 436
#define ERR_NEEDMOREPARAMS 461
#define ERR_NOPRIVILEGES 481


std::string to_string(int toConvert);
