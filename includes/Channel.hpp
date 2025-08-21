/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:45:46 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/19 18:41:48 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <set>
#include "User.hpp"

class Channel
{
private:
	std::string		name;
	std::string		password;
	bool			invite_only;
	// bool			user_limit;
	// int			user_limit_nb;
	std::set <User> operators; // evite doublons contrairement vector , recherche rapide = find 
	std::set <User> users;
	std::string		admin;


public:
	Channel();
	Channel(std::string name, std::string admin);
	Channel(const Channel &src);
	Channel	operator=(const Channel &src);
	~Channel();

	Channel(const std::string &name);
};
