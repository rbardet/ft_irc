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

class Channel
{
private:
	std::string	name;
	std::string	password;
	bool		invite_only;
public:
	Channel();
	Channel(const Channel &src);
	Channel	operator=(const Channel &src);
	~Channel();

	Channel(const std::string &name);
};
