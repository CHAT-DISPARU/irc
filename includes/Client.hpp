/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:54:43 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/07 13:57:09 by gajanvie         ###   ########.fr       */
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

class	Client
{
	private:
		int			fd;
		std::string	_nickname;
		std::string	_realname;
		std::string	_username;
		std::string	_ip;
		std::string	_sendBuffer;
		std::string	_buffer;
		bool		auth;
		time_t		_last_activity;
		bool		complete;
		bool		_ping_sent;

	public:
		Client(int fd) : fd(fd), auth(false), complete(false), _ping_sent(false)
		{
			_last_activity = time(NULL);
		}
		~Client(){}
		int					get_fd() const;
		const std::string&	get_nick() const;
		const std::string&	get_buff() const;
		const std::string&	get_user() const;
		const std::string&	get_real() const;
		bool				is_auth() const;
		bool				is_complete() const;
		
		void	set_nick(const std::string& str);
		void	set_buff(const std::string& str);
		void	set_user(const std::string& str);
		void	set_real(const std::string& str);
		void	set_auth(bool status);
		void	set_complete(bool status);
		
		void		ClearBuff();
		void		EraseLine(size_t pos);
		void		add_to_buff(const std::string& str);
		const		std::string& get_sendBuff() const { return _sendBuffer; }
		void		add_to_sendBuff(const std::string& str) { _sendBuffer += str; }
		void		erase_sendBuff(size_t pos) { _sendBuffer.erase(0, pos); }
		bool		hasDataToSend() const { return !_sendBuffer.empty(); }
		bool		checknick(const std::string& nick) const;
		std::string	get_nick_or_star() const;
		const		std::string& get_ip() const;
		void		set_ip(const std::string& ip);
		time_t		get_last_activity() const;
		void		set_last_activity(time_t time);
		void		set_ping_sent(bool status);
		bool		get_ping_sent() const;
};

