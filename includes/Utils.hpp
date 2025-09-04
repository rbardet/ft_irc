/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:39:17 by rbardet-          #+#    #+#             */
/*   Updated: 2025/09/04 20:29:18 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>

#define PORT 1
#define PASSWORD 2

#define SERV_NAME "ircserv"

#define MODE_CMD 5

#define NICK_CMD 5
#define USER_CMD 5

#define REMOVE_LIMIT 0

#define ERR_NOSUCHCHANNEL "403"
#define ERR_CANNOTSENDTOCHAN "404"
#define ERR_NONICKNAMEGIVEN "431"
#define ERR_NICKCOLLISION "436"
#define ERR_NEEDMOREPARAMS "461"
#define ERR_NOPRIVILEGES "481"

#define RPL_WELCOME "001"
#define RPL_YOURHOST "002"
#define RPL_CREATED "003"

#define ERR_NONICKNAMEGIVEN "431"
#define ERR_NICKCOLLISION "436"
#define ERR_USERNOTINCHANNEL "441"
#define ERR_NEEDMOREPARAMS "461"
#define ERR_NOPERMFORHOST "463"
#define ERR_INVALIDUSERNAME "468"
#define ERR_UNKNOWNMODE "472"

const std::string getParam(int cmdLength, const std::string &line);
