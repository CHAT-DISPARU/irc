/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:54:46 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/08 13:56:06 by gajanvie         ###   ########.fr       */
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
#include <CommandParser.hpp>
#include <cerrno>
#include <Channel.hpp>
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

class Server
{
	private:
		std::string							_password;
		std::map<int, Client *>				clients;
		std::map<std::string, Channel *>	channels;
		std::vector<struct pollfd>			pollfd;
		int									fdsocket;
		int									port;
		static bool							signal;
		CommandParser						_parser;
	public:
		static void	SignalHandler(int signum);
		Server(){fdsocket = -1;}
		~Server();
		void		disconect_client(int fd);
		void		ServerInit(int port, std::string password);
		const std::string& getPassword() const { return _password; }
		void		SerSocket();
		void		AcceptNewClient();
		void		ReceiveNewData(int fd);
		void		run();
		void		SendData(int fd);
		void		sendReply(int fd, const std::string& code, const std::string& target, const std::string& message);
		Client*		getClientByNick(const std::string& nick);
		bool		checknickuse(const std::string& nick);
		bool		checkRegistration(Client* client);
		bool		alreadyRegistered(Client* client);
		bool		isAuthenticated(Client* client);
		bool		hasEnoughParams(Client* client, const std::string& commandName, const std::vector<std::string>& args, size_t requiredSize);
		void		sendWelcome(Client* client);
		Channel*	getChannel(const std::string& name);
		void		addChannel(Channel* channel);
};


