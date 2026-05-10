/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 18:18:20 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/11 00:38:07 by CHAT-DISPAR      ###   ########.fr       */
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
#include <cerrno>
#include <cstdlib>

class	Bot
{
	private:
		std::string	_host;
		int			_port;
		std::string	_password;
		std::strsing	_nickname;
		int			_socketFd;
		bool		_isRunning;
		std::vector<std::string>	_bonjourUsers;
		std::vector<std::string>	_curse;
		std::map<std::string, bool>	_channelOp;

		void	_connectToServer();
		void	_authenticate();
		void	_listenLoop();
		void	_sendMessage(const std::string& message) const;
		//reste a faire 
		void	_processMessage(const std::string& message);
		void	_PrivMsg_bot(const std::string& sender, const std::string& target, const std::string& content);
		void	_Invite_bot(const std::string& sender, const std::string& channel);
		void	_Who_bot(const std::string& line);
		void	_Mode_bot(const std::string& line);
		void	_sendbonjour_client(const std::string& targetUser);
		void	_joinandintroduce(const std::string& channel);
		void	_checkcurse(const std::string& sender, const std::string& channel, const std::string& content);
		void	_loadCurse();

	public:

		Bot(const std::string& host, int port, const std::string& password, const std::string& nickname);
		~Bot();

		void	start();
		void	stop();
};
