/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:39:17 by rbardet-          #+#    #+#             */
/*   Updated: 2025/09/05 19:35:26 by rbardet-         ###   ########.fr       */
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
#define CMD_TOPIC "TOPIC"

#define MODE_CMD_LENGTH 5
#define NICK_CMD_LENGTH 5
#define USER_CMD_LENGTH 5
#define PASS_CMD_LENGTH 5
#define TOPIC_CMD_LENGTH 6

#define MODE_FLAG 1

#define REMOVE_LIMIT 0

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

#define MSG_ERR_PASSWDMISMATCH "Wrong password"
#define MSG_ERR_WRONGUSER "This user does not exist"
#define MSG_ERR_NEEDMOREPARAMS "No param given to the command"
#define MSG_ERR_NOPERMS "You have no perm on this channel"
#define MSG_ERR_USERNOTINCHANNEL "This user is not in the channel"
#define MSG_ERR_NICKCOLLISION "This nickname is already in use"
#define MSG_ERR_UNKNOWNCOMMAND " This command is unknown"
#define MSG_NEED_PASS "This server has a password enter it before using it"
#define MSG_NEED_NICK "You have no nickname, enter one </nick>"
#define MSG_NEED_USER "You have no username, enter one </user>"
#define MSG_SUCCESS_KICK "The user got kicked from the channel"

const std::string getParam(int cmdLength, const std::string &line);
