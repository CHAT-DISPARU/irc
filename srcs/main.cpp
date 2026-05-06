/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:05:27 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/06 10:45:36 by gajanvie         ###   ########.fr       */
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