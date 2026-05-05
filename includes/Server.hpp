/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:54:46 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/05 12:56:03 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <csignal>
#include <vector>
#include <map>
#include <cstring>
#include <Client.hpp>

class Server
{
	private:
		std::map<int, Client *> clients;
		std::vector<struct pollfd>	pollfd;
		int							fdsocket;
		int							port;
		//static bool					signal;
	public:
		Server(){fdsocket = -1;}
		~Server();
		void		ServerInit(int port);
		void		SerSocket();
		void		AcceptNewClient();
		void		ReceiveNewData(int fd);
		void		run();
};


