/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:30:37 by rbardet-          #+#    #+#             */
/*   Updated: 2025/09/04 16:36:02 by rbardet-         ###   ########.fr       */
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
	int			epollFd;
	epoll_event	event;
	epoll_event	events[MAX_EVENTS];
	std::map<int, User>	Users;
public:
	Server();
	Server(const Server &src);
	Server operator=(const Server &src);
	~Server();

	static bool running;
	void	initSocket();
	void	initEpoll();
	void	initServer(const int &port, const std::string &password);
	void	runServer();
	static void	signalHandler(int signum);
	void	acceptUser();
	void	parseInput(int userFd);
	void	sendMessage(int &clientFd, int code, const std::string &message) const;
	void	handleCapReq(const int &userFd)const;
	void	handleNick(int clientFd, const std::string &line);
	void	handleUsername(int clientFd, const std::string &line);
	void	handleLine(int clientFd, const std::string &line);
	void	handleJoin(int clientFd, const std::string &line);

	bool	nickAlreadyInUse(const std::string &nick);

	//   JOIN
	std::string	parseJoinChannelName(const std::string &line);
	bool		channelExists(const std::string &channelName);
	void		createChannel(const std::string &channelName, int creatorFd);
	void		joinExistingChannel(const std::string &channelName, int userFd);

	// Messages dans les channels (chat normal IRC) irssi écrit privmsg direct
	void		handleChannelMessage(int clientFd, const std::string &line);
	void		broadcastToChannel(const std::string &channelName, const std::string &message, int senderFd);

	//  MODE
	void		handleMode(int clientFd, const std::string &line);
	void 		execMode(int clientFd, const std::string &channelName, const std::string &mode);
	void 		setMode(int clientFd, const std::string &channelName, char mode, bool set_or_unset);
	char		extractFlag(const std::string &mode);

};
