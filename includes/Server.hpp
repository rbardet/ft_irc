/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:30:37 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/22 18:42:21 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <set>
#include "Channel.hpp"
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <signal.h>
#include <map>
#include "User.hpp"
#include <fcntl.h>

#define MAX_USER 1024
#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

class Server
{
private:
	int			port;
	int			socketfd;
	std::string	password;
	std::vector<Channel>	channelList;
	static bool running;
	int			epollFd;
	epoll_event	event;
	epoll_event	events[MAX_EVENTS];
	std::map<int, User>	Users;
public:
	Server();
	Server(const Server &src);
	Server operator=(const Server &src);
	~Server();

	void	initSocket();
	void	initEpoll();
	void	initServer(const int &port, const std::string &password);
	void	runServer();
	static void	signalHandler(int signum);
	void	acceptUser();
	void	parseInput(int userFd);
	void	sendMessage(const int &userFd, const int &code) const;
	void	handleCapReq(const int &userFd)const;
	void	handleNick(int clientFd, const std::string &line);
	void	handleLine(int clientFd, const std::string &line);
};
