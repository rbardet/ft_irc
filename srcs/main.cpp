/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:54:32 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/19 17:36:40 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/Server.hpp"
#include <sys/types.h>
#include <sys/socket.h>

int main(int ac, char **av) {
	(void)av;
	if (ac != 3) {
		std::cout << "usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	pollfd *pol = new pollfd;
	nfds_t fd = sockfd;
	pol->fd = sockfd;
	int j = poll(pol, fd, 0);
	std::cout << "i = " << sockfd << std::endl;
	std::cout << "j = " << j << std::endl;
	return (0);
}
