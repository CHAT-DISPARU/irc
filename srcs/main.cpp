/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:05:27 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/11 20:16:15 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <stdlib.h>
#include <iostream>
#include <exception>

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
	if (ac != 3)
	{
		std::cerr << "Usage: ./irc <port> <password>" << std::endl;
		return (1);
	}
	std::string	port_str = av[1];
	std::string	password = av[2];

	if (!is_valid_port(port_str))
	{
		std::cerr << "Error: Invalid port  it must be a number between 1 and 65535." << std::endl;
		return (1);
	}
	if (password.empty())
	{
		std::cerr << "Error: Password cannot be empty." << std::endl;
		return (1);
	}
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, Server::SignalHandler);
	signal(SIGQUIT, Server::SignalHandler);
	try
	{
		Server	server;

		server.ServerInit(std::atoi(port_str.c_str()), password);
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
