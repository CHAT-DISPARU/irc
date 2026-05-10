/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:38:42 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/11 00:38:10 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Bot.hpp>

Bot::Bot(const std::string& host, int port, const std::string& password, const std::string& nickname)
	: _host(host), _port(port), _password(password), _nickname(nickname), 
	  _socketFd(-1), _isRunning(false)
{
	std::cout << "Initialisation du bot " << _nickname << " pour " << _host << ":" << _port << std::endl;
}

void Bot::start()
{
	_isRunning = true;
	try
	{
		_connectToServer();
		_authenticate();
		std::cout << "Bot connected and auth, Start of listen..." << std::endl;
		_listenLoop();
	} catch (const std::exception& e)
	{
		std::cerr << "Eror : " << e.what() << std::endl;
		stop();
	}
}

void Bot::stop()
{
	_isRunning = false;
	if (_socketFd != -1)
	{
		close(_socketFd);
		_socketFd = -1;
		std::cout << "Connexion bot ended." << std::endl;
	}
}

void Bot::_connectToServer()
{
	_socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketFd == -1)
		throw std::runtime_error("socket bot");

	struct	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(_port);
	serverAddr.sin_addr.s_addr = inet_addr(_host.c_str());

	if (serverAddr.sin_addr.s_addr == INADDR_NONE)
		throw std::runtime_error("Erreur : IP invalid (" + _host + ")");

	if (connect(_socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
		throw std::runtime_error("Connexion au serveur échouée.");
}

void	Bot::_sendMessage(const std::string& message) const
{
	if (_socketFd == -1)
		return;
	ssize_t	bytesSent = send(_socketFd, message.c_str(), message.length(), 0);
	if (bytesSent == -1)
		std::cerr << "Error send : " << message << std::endl;
	else
		std::cout << "Bot said -> " << message;
}

void Bot::_authenticate()
{
	_sendMessage("PASS " + _password);
	_sendMessage("NICK " + _nickname);
	_sendMessage("USER " + _nickname + " 0 * :" + _nickname + " le Plot");
}

void Bot::_listenLoop()
{
	char		buffer[1024];
	std::string	dataBuffer = "";

	while (_isRunning)
	{
		std::memset(buffer, 0, sizeof(buffer));
		ssize_t	bytesReceived = recv(_socketFd, buffer, sizeof(buffer) - 1, 0);

		if (bytesReceived < 0)
		{
			std::cerr << "Error recv" << std::endl;
			break ;
		}
		else if (bytesReceived == 0)
		{
			std::cout << "Server closed." << std::endl;
			break ;
		}
		dataBuffer += buffer;
		size_t	pos;
		while ((pos = dataBuffer.find("\r\n")) != std::string::npos)
		{
			std::string line = dataBuffer.substr(0, pos);
			dataBuffer.erase(0, pos + 2);

			std::cout << "Serveur -> " << line << std::endl;
			_processMessage(line);
		}
	}
	stop();
}
