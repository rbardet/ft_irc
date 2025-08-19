/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:54:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/19 18:18:26 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "../includes/Server.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //-> for sockaddr_in
#include <netdb.h>// -> gethostbyname
#include <arpa/inet.h> // inet 

#define PORT 1
#define PASSWORD 2

int main(int ac, char **av) 
{
	struct sockaddr_in serv_address;
	hostent* localHost; // struct qui stock le localhost

	if (ac != 3) {
		std::cout << "usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}

	try 
	{
		Server serv(atoi(av[PORT]), av[PASSWORD]);
	}
	catch(const std::exception& e) 
	{
		std::cerr << e.what() << '\n';
	}

	int listen_sockfd = socket(AF_INET, SOCK_STREAM, 0); // domaine (type adress supportes v4 v6), type de socket, protocol en fonction des 2 premiers 
	pollfd *pol = new pollfd;
	nfds_t fd = listen_sockfd;
	pol->fd = listen_sockfd;
	int j = poll(pol, fd, 0);
	
	localHost = gethostbyname("");

	serv_address.sin_family = AF_INET;
	serv_address.sin_addr.s_addr = inet_addr(); // convertit internet host adress en network adress (change bit order)  (endianness)
	serv_address.sin_port = htons(5959); // same

	std::cout << "i = " << listen_sockfd << std::endl;
	std::cout << "j = " << j << std::endl;

	bind(listen_sockfd, serv_address, sizeof(serv_address));

	return (0);
}

