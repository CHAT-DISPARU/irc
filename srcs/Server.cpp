/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:05:31 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/05 13:07:06 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	Server::SerSocket()
{
	this->fdsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fdsocket < 0)
		throw (std::runtime_error("error : Socket Creation"));
	if (fcntl(this->fdsocket, F_SETFL, O_NONBLOCK) == -1)
		throw (std::runtime_error("error : fcntl"));
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

void	Server::AcceptNewClient()
{
	struct sockaddr_in	addr;
	socklen_t len = sizeof(addr);
	int				new_client_fd;

	new_client_fd = accept(this->fdsocket, (struct sockaddr *)&addr, &len);
	if (new_client_fd == -1)
	{
		std::cerr << "Error : Accept new Client" << std::endl;
		return ;
	}
	if (fcntl(new_client_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "Error : fcntl new Client" << std::endl;
		return ;
	}
	struct pollfd pollfd_server;

	pollfd_server.fd = new_client_fd;
	pollfd_server.events = POLLIN;
	this->pollfd.push_back(pollfd_server);
	std::cout << "New client FD : [" << new_client_fd << "]" << std::endl;
	this->clients[new_client_fd] = new Client(new_client_fd);
}

void	Server::ReceiveNewData(int fd)
{
	char	buffer[1024];
	ssize_t	byte_r;
	
	std::memset(buffer, 0, sizeof(buffer));
	byte_r = recv(fd, buffer, sizeof(buffer) - 1, 0);
	if (byte_r <= 0)
	{
		if (byte_r < 0)
		{
			std::cerr << "Error : read Client" << std::endl;
			return ;
		}
		else
		{
			close (fd);
			std::cout << "the client : FD [" << fd << "] disconnected" << std::endl;
			delete this->clients[fd];
			clients.erase(fd);
			
			for (std::vector <struct pollfd>::iterator it = pollfd.begin(); it != pollfd.end(); it++)
			{
				if (it->fd == fd)
				{
					pollfd.erase(it);
					return ;
				}
			}
		}
	}
	std::string	data(buffer);

	std::cout << data;
	this->clients[fd]->add_to_buff(data);
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
		for (size_t i = 0; i < pollfd.size(); i++)
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

Server::~Server()
{
	for (std::vector <struct pollfd>::iterator it = pollfd.begin(); it != pollfd.end(); it++)
	{
		delete clients[it->fd];
		close(it->fd);
	}
	pollfd.erase(pollfd.begin(), pollfd.end());
	if (clients.size() > 0)
		clients.clear();
	if (fdsocket != -1)
		close (fdsocket);
}