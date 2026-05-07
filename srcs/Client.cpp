/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolavale <rolavale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:17:00 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/07 16:40:50 by rolavale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>

int	Client::get_fd() const
{
	return (this->fd);
}
const std::string&	Client::get_nick() const
{
	return (this->_nickname);
}
const std::string&	Client::get_buff() const
{
	return (this->_buffer);
}
const std::string&	Client::get_user() const
{
	return (this->_username);
}
const std::string&	Client::get_real() const
{
	return (this->_realname);
}
bool	Client::is_auth() const
{
	return (this->auth);
}
bool	Client::is_complete() const
{
	return (this->complete);
}

void	Client::set_nick(const std::string& str)
{
	this->_nickname = str;
}
void	Client::set_buff(const std::string& str)
{
	this->_buffer = str;
}
void	Client::set_user(const std::string& str)
{
	this->_username = str;
}
void	Client::set_real(const std::string& str)
{
	this->_realname = str;
}
const std::string&	Client::get_ip() const
{
	return _ip;
}
void	Client::set_ip(const std::string& ip)
{
	_ip = ip;
}

time_t	Client::get_last_activity() const
{
	return _last_activity;
}

void	Client::set_ping_sent(bool status)
{
	this->_ping_sent = status;
}

void	Client::set_last_activity(time_t time)
{
	_last_activity = time;
}

bool		Client::get_ping_sent() const
{
	return (this->_ping_sent);
}

void	Client::set_auth(bool status)
{
	this->auth = status;
}
void	Client::set_complete(bool status)
{
	this->complete = status;
}

void	Client::ClearBuff()
{
	this->_buffer.erase();
}

void	Client::EraseLine(size_t pos)
{
	this->_buffer.erase(0, pos);
}

void	Client::add_to_buff(const std::string& str)
{
	this->_buffer += str;
}

std::string	Client::get_nick_or_star() const
{
	return _nickname.empty() ? "*" : _nickname;
}

bool isIrcSpecial(char c)
{
	return c == '[' || c == ']' || c == '\\' || c == '`' || 
		   c == '_' || c == '^' || c == '{' || c == '|' || c == '}';
}

bool	Client::checknick(const std::string& nick) const
{
	if (nick.empty() || nick.length() > 9)
		return false;

	char first = nick[0];
	if (!std::isalpha(first) && !isIrcSpecial(first))
		return false;
	for (size_t i = 1; i < nick.length(); ++i)
	{
		char c = nick[i];
		if (!std::isalpha(c) && !std::isdigit(c) && !isIrcSpecial(c) && c != '-')
			return false;
	}
	return (true);
}
