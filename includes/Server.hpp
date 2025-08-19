/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:30:37 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/19 16:36:19 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <poll.h>

class Server
{
private:
	int			port;
	std::string	password;
public:
	Server();
	Server(const Server &src);
	Server operator=(const Server &src);
	~Server();

	Server(const int &port, const std::string &password);
};
