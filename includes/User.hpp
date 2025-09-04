/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:11:58 by rbardet-          #+#    #+#             */
/*   Updated: 2025/08/21 15:53:35 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <unistd.h>

class User
{
private:
	std::string	nickname;
	std::string	username;
	std::string input;
	int			fd;

	bool		hasNickname;
	bool		hasUsername;
	bool		hasPass;
	bool		isRegister;
public:
	User();
	User(const User &src);
	User &operator=(const User &src);
	~User();

	User(const std::string &nickname, const std::string &username);
	void setFd(const int &fd);
	void setNickname(const std::string &nickname);
	void setUsername(const std::string &username);

	void closeConnection();
	const std::string &getNickname() const {return (nickname);};
	const std::string &getUsername() const {return (username);};
	std::string &getInput() {return (input);};
	const int &getFd() const {return (fd);};
	const bool &getIsRegister() const {return (isRegister);};
	void setHasNickname () {this->hasNickname = true;};
	void setHasUsername() {this->hasUsername = true;};
	void setHasPass() {this->hasPass = true;};
	const bool &getHasNickname() {return (this->hasNickname);};
	const bool &getHasUsername() {return (this->hasUsername);};
	const bool &getHasPass() {return (this->hasPass);};
	void tryRegisterUser();
};
