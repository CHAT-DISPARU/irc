/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:17:00 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/05 19:41:36 by CHAT-DISPAR      ###   ########.fr       */
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