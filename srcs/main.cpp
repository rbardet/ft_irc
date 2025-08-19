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

#define PORT 1
#define PASSWORD 2

int main(int ac, char **av) {

	if (ac != 3) {
		std::cout << "usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	try {
		Server serv(atoi(av[PORT]), av[PASSWORD]);
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);
}
