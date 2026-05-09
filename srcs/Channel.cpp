/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:03:05 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/09 14:44:37 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

Channel::Channel(std::string name) : _name(name), _user_limit(0)
{
	for (int i = 0; i < 5; i++)
		_modes[i] = false;
}

Channel::~Channel() {}

const std::string&	Channel::getName() const
{
	return _name;
}

const std::string&	Channel::getTopic() const
{
	return _topic;
}

bool	Channel::hasMode(char c) const
{
	if (c == 'i')
		return _modes[0];
	if (c == 't')
		return _modes[1];
	if (c == 'k')
		return _modes[2];
	if (c == 'o')
		return _modes[3];
	if (c == 'l')
		return _modes[4];
	return false;
}

bool	Channel::isFull() const
{
	if (_modes[4] && _user_limit > 0)
		return _members.size() >= _user_limit;
	return false;
}

bool	Channel::isInvited(int fd) const
{
	for (size_t i = 0; i < _invited_fds.size(); i++)
	{
		if (_invited_fds[i] == fd)
			return true;
	}
	return false;
}

bool	Channel::checkKey(const std::string& key) const
{
	if (!_modes[2])
		return true;
	return (_pass == key);
}

void	Channel::setMode(char c, bool status)
{
	if (c == 'i')
		_modes[0] = status;
	if (c == 't')
		_modes[1] = status;
	if (c == 'k')
		_modes[2] = status;
	if (c == 'o')
		_modes[3] = status;
	if (c == 'l')
		_modes[4] = status;
}

void	Channel::setTopic(const std::string& topic)
{
	_topic = topic;
}

void	Channel::setKey(const std::string& key)
{
	_pass = key;
}

void	Channel::setLimit(size_t limit)
{
	_user_limit = limit;
}

void	Channel::addMember(Client *client)
{
	if (client)
		_members[client->get_fd()] = client;
}

void	Channel::addOperator(Client *client)
{
	if (client)
		_operators[client->get_fd()] = client;
}

void	Channel::removeMember(int fd)
{
	_members.erase(fd);
	_operators.erase(fd);
	for (std::vector<int>::iterator it = _invited_fds.begin(); it != _invited_fds.end(); ++it)
	{
		if (*it == fd)
		{
			_invited_fds.erase(it);
			break;
		}
	}
}

void	Channel::removeOperator(int fd)
{
	_operators.erase(fd);
}

void	Channel::addInvite(int fd)
{
	if (!isInvited(fd))
		_invited_fds.push_back(fd);
}

void	Channel::broadcast(const std::string& message, int excludeFd)
{
	std::map<int, Client *>::iterator it;
	for (it = _members.begin(); it != _members.end(); ++it)
	{
		if (it->first != excludeFd)
			it->second->add_to_sendBuff(message);
	}
}

std::string	Channel::getClientList()
{
	std::string							list = "";
	std::map<int, Client *>::iterator	it;

	for (it = _members.begin(); it != _members.end(); ++it)
	{
		if (_operators.find(it->first) != _operators.end())
			list += "@";
		list += it->second->get_nick() + " ";
	}
	return (list);
}

bool	Channel::is_inChannel(Client *client)
{
	std::map<int, Client *>::iterator	it;
	
	for (it = _members.begin(); it != _members.end(); ++it)
	{
		if (it->second == client)
			return (true);
	}
	return (false);
}

bool	Channel::isOperator(Client *client)
{
	if (_operators.find(client->get_fd()) != _operators.end())
		return (true);
	return (false);
}

void	Channel::removeInvite(int fd)
{
	for (std::vector<int>::iterator it = _invited_fds.begin(); it != _invited_fds.end(); ++it)
	{
		if (*it == fd)
		{
			_invited_fds.erase(it);
			return;
		}
	}
}

bool	Channel::isEmpty() const
{
	return (_members.empty());
}

std::map<int, Client*>	Channel::getMembers() const
{
	return _members;
}

size_t	Channel::get_limit() const
{
	return (this->_user_limit);
}