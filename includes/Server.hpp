#pragma once

#include <iostream>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <set>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <signal.h>
#include <map>
#include <fcntl.h>

#include "User.hpp"
#include "Channel.hpp"
#include "Utils.hpp"

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
	bool	hasPassword() const;
	void	sendRPL(const int &clientFd, const std::string code, const std::string &nick, const std::string &message) const;
	void	handleNick(const int &clientFd, const std::string &line);
	void	handleUsername(const int &clientFd, const std::string &line);
	void	handleLine(const int &clientFd, const std::string &line);
	void	handleJoin(const int &clientFd, const std::string &line);
	void	handlePass(const int &clientFd, const std::string &line);
	void	handleTopic(const int &clientFd, const std::string &line);
	void	handleKick(const int &clientFd, const std::string &line);
	void	handlePing(const int &clientFd, const std::string &line);

	const	std::string getUserToKick(const std::string &line) const;
	const	std::string getChannelName(const std::string &line) const;

	const	std::string getTopic(const std::string &line) const;

	bool		nickAlreadyInUse(const std::string &nick);
	void		welcomeUser(const int &code, const std::string &name) const;
	int			findIdByName(const std::string &name);
	std::string	findNameById(const int &clientFd);

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
	void 		execMode(int clientFd, const std::string &channelName, const std::string &mode, std::string arg = "");
	void 		setMode(int clientFd, const std::string &channelName, char mode, bool set_or_unset, std::string arg = "");
	char		extractFlag(const std::string &mode);

};
