/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:39:17 by rbardet-          #+#    #+#             */
/*   Updated: 2025/09/05 18:26:17 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>

#define PORT 1
#define PASSWORD 2

#define SERV_NAME "ircserv"

#define CMD_MODE "MODE"
#define CMD_NICK "NICK"
#define CMD_USER "USER"
#define CMD_PASS "PASS"
#define CMD_JOIN "JOIN"
#define CMD_KICK "KICK"
#define CMD_PRIVMSG "PRIVMSG"

#define MODE_CMD_LENGTH 5
#define NICK_CMD_LENGTH 5
#define USER_CMD_LENGTH 5
#define PASS_CMD_LENGTH 5

#define MODE_CHAR 1

#define REMOVE_LIMIT 0

#define TO_BE_ON_INDEX_OF_CHANNEL 1
#define TO_BE_ON_INDEX_OF_MODE 1
#define TO_BE_ON_ON_INDEX_OF_ARG 4

#define RPL_WELCOME "001"
#define RPL_YOURHOST "002"
#define RPL_CREATED "003"

#define ERR_NOSUCHCHANNEL "403"
#define ERR_CANNOTSENDTOCHAN "404"
#define ERR_UNKNOWNCOMMAND "421"
#define ERR_NONICKNAMEGIVEN "431"
#define ERR_NICKCOLLISION "436"
#define ERR_USERNOTINCHANNEL "441"
#define ERR_NOTREGISTERED "451"
#define ERR_NEEDMOREPARAMS "461"
#define ERR_NOPERMFORHOST "463"
#define ERR_PASSWDMISMATCH "464"
#define ERR_INVALIDUSERNAME "468"
#define ERR_KICKEDFROMCHAN	"470"
#define ERR_UNKNOWNMODE "472"
#define ERR_NOPRIVILEGES "481"


const std::string getParam(int cmdLength, const std::string &line);
