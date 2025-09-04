/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:47:59 by rbardet-          #+#    #+#             */
/*   Updated: 2025/09/04 19:25:00 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Utils.hpp"

const std::string getParam(int cmdLength, const std::string &line) {
	std::string args = line.substr(cmdLength);
	std::string firstParam = args.substr(0, args.find(' '));
	return(firstParam);
}
