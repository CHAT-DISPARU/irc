/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:37:40 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/11 20:26:39 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <iostream>
#include <stdlib.h>

bool	is_valid_port(const std::string& port_str)
{
	if (port_str.empty())
		return (false);
	
	for (size_t i = 0; i < port_str.length(); i++)
	{
		if (!std::isdigit(port_str[i]))
			return (false);
	}
	long	port = std::atol(port_str.c_str());
	if (port < 1 || port > 65535)
		return (false);
		
	return (true);
}

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		std::cerr << "Usage: ./bot <host> <port> <password> <nickname> [curse data base]" << std::endl;
		return (1);
	}
	std::string	host = av[1];
	std::string	port_str = av[2];
	std::string	password = av[3];
	std::string	nickname = av[4];
	std::string	db_curse = ac == 6 ? av[5] : "";
	if (host.empty())
	{
		std::cerr << "Error: Host cannot be empty." << std::endl;
		return (1);
	}
	if (!is_valid_port(port_str))
	{
		std::cerr << "Error: Invalid port it must be a number between 1 and 65535." << std::endl;
		return (1);
	}
	if (password.empty() || nickname.empty())
	{
		std::cerr << "Error: Password and nickname cannot be empty." << std::endl;
		return (1);
	}
	try
	{
		Bot	ircBot(host, std::atoi(port_str.c_str()), password, nickname);
		if (ac == 6)
			ircBot.loadCurse(db_curse);
		ircBot.start();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Bot Error : " << e.what() << std::endl;
		return (1);
	}

	return (0);
}
