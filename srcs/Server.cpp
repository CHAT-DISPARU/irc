/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:05:31 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/04 17:33:27 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	Server::SerSocket()
{
	this->fdsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fdsocket < 0)
		throw (std::runtime_error("error : Socket Creation"));
	int	opt = 1;
	if (setsockopt(fdsocket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) == -1)
		throw (std::runtime_error("error : Socket option"));
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(fdsocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		throw (std::runtime_error("error : Socket bind"));
	if (listen(fdsocket, SOMAXCONN) == -1)
		throw (std::runtime_error("error : Socket listen"));
}

void	Server::ServerInit(int port)
{
	this->port = port;
	SerSocket();
}

void	Server::run(void)
{	
	struct pollfd pollfd_server;
	
	pollfd_server.fd = fdsocket;
	pollfd_server.events = POLLIN;
	this->pollfd.push_back(pollfd_server);
	std::cout << "Waiting client ..." << std::endl;
	while (1)
	{
		if (poll(&pollfd[0], pollfd.size(), -1) == -1)
			throw(std::runtime_error("poll() faild"));
		for (int i = 0; i < pollfd.size(); i++)
		{
			if (pollfd[i].revents & POLLIN)
			{
				if (pollfd[i].fd == this->fdsocket)
					AcceptNewClient();
				else
					ReceiveNewData(pollfd[i].fd);
			}
		}
	}
}
