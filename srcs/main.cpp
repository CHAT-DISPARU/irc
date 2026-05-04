/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:05:27 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/04 17:11:42 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "./irc ......" << std::endl;
		return (1);
	}
	Server  server;

	server.ServerInit(atoi(av[1]));
	return (1);
}