/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:17:00 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/06 11:50:03 by gajanvie         ###   ########.fr       */
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
