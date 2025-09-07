#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "../../includes/Utils.hpp"

#define FILE "./srcs/message.txt"

class Bot {
private:
	int			fd;
	int			port;
	std::string	password;
	std::string	ip;

	std::vector<std::string> messages;
public:
	static bool	running;
	static void	signalHandler(int signum);

	Bot();
	Bot(const Bot &src);
	Bot operator=(const Bot &src);
	~Bot();

	Bot(const int port, const std::string password, const std::string ip);
	void	loadWelcomeMessages();
	void	printMessage();

	const int &getFd() const {return(this->fd);};
	const int &getport() const {return(this->port);};
	const std::string &getpassword() const {return(this->password);};
	const std::string &getip() const {return(this->ip);};

	void	connect();
};

