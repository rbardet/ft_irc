/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:47:59 by rbardet-          #+#    #+#             */
/*   Updated: 2025/09/04 17:49:10 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Utils.hpp"

std::string to_string(int toConvert) {
	std::ostringstream oss;
	oss << toConvert;
	return (oss.str());
}

const std::string getParam(int cmdLength, const std::string &line) {
	std::string args = line.substr(cmdLength);
	std::string firstParam = args.substr(0, args.find(' '));
	std::cout << firstParam << std::endl;
	return(firstParam);
}
