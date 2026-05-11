/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:37:40 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/11 12:30:48 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <iostream>
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac != 5)
	{
		std::cerr << "Usage: ./bot <host> <port> <password> <nickname>" << std::endl;
		return (1);
	}
	std::string	host = av[1];
	int			port = atoi(av[2]);
	std::string	password = av[3];
	std::string	nickname = av[4];

	try
	{
		Bot ircBot(host, port, password, nickname);
		ircBot.start();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Bot Error : " << e.what() << std::endl;
		return (1);
	}

	return (0);
}