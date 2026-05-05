/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:05:27 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/05 19:41:32 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <stdlib.h>
#include <iostream>
#include <exception>

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Usage: ./irc <port> <password>" << std::endl;
		return (1);
	}
	signal(SIGINT, Server::SignalHandler);
	signal(SIGQUIT, Server::SignalHandler);
	try
	{
		Server  server;

		server.ServerInit(atoi(av[1]), av[2]);
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Erreur critique : " << e.what() << std::endl;
		return (1);
	}
	return (0);
}