/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 18:18:20 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/11 21:05:10 by CHAT-DISPAR      ###   ########.fr       */
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
#include <sstream>
#include <fstream>

class	Bot
{
	private:
		std::string	_host;
		int			_port;
		std::string	_password;
		std::string	_nickname;
		int			_socketFd;
		bool		_isRunning;
		time_t		_last_bonjour;
		std::vector<std::string>	_bonjourUsers;
		std::vector<std::string>	_curse;
		std::map<std::string, bool>	_channelOp;

		void	_connectToServer();
		void	_authenticate();
		void	_listenLoop();
		void	_sendMessage(const std::string& message) const;
		void	_call_funcs(std::string func, const std::vector<std::string>& args, const std::string& nick);
		void	_processMessage(const std::string& message);
		void	_Who_bot(const std::vector<std::string>& arg, const std::string& nicks);
		void	_sendbonjour_client(const std::string& targetUser);
		void	_PrivMsg_bot(const std::vector<std::string>& args, const std::string& nick);
		void	_joinandintroduce(const std::string& channel);
		void	_Invite_bot(const std::vector<std::string>& args, const std::string& nick);
		void	_Mode_bot(const std::vector<std::string>& args, const std::string& nick);
		void	_NoSuchNick_bot(const std::vector<std::string>& args, const std::string& nick);
		void	_botCommand(const std::string& cmd, const std::string& nick, const std::string& target, const std::string& target_user);
		void	_checkcurse(const std::string& sender, const std::string& channel, const std::string& content);

	public:

		Bot(const std::string& host, int port, const std::string& password, const std::string& nickname);
		~Bot();

		void	start();
		void	loadCurse(const std::string& db_path);
		void	stop();
};
