/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:54:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/20 14:39:47 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <signal.h>
#include "../includes/Server.hpp"
#include "../includes/Utils.hpp"


void setupSignal()
{
	signal(SIGINT, Server::signalHandler);


}

int main(int ac, char **av) {

	if (ac != 3) {
		std::cout << "usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	try {
		Server serv;
		setupSignal();
		serv.initServer(std::atoi(av[PORT]), av[PASSWORD]);
		serv.RunServer();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);
}
