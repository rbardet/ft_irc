/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:11:58 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/19 14:45:16 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Client
{
private:
	std::string	nickname;
	std::string	username;
public:
	Client();
	Client(const Client &src);
	Client operator=(const Client &src);
	~Client();

	Client(const std::string &nickname, const std::string &username);
};
