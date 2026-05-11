/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:38:42 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/11 17:02:38 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Bot.hpp>

Bot::Bot(const std::string& host, int port, const std::string& password, const std::string& nickname)
	: _host(host), _port(port), _password(password), _nickname(nickname), 
	  _socketFd(-1), _isRunning(false)
{
	std::cout << "Initialisation du bot " << _nickname << " pour " << _host << ":" << _port << std::endl;
}

Bot::~Bot() {}

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
	for (std::map<std::string, bool>::iterator it = _channelOp.begin(); it != _channelOp.end(); it++)
	{
		std::string	msg = "PART " + it->first;
		_sendMessage(msg);
	}
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
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 500*1000;
	if (setsockopt(_socketFd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval)) == -1)
		throw std::runtime_error(std::strerror(errno));
	struct	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(_port);
	serverAddr.sin_addr.s_addr = inet_addr(_host.c_str());

	if (serverAddr.sin_addr.s_addr == INADDR_NONE)
		throw std::runtime_error("Erreur : IP invalid (" + _host + ")");

	if (connect(_socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
		throw std::runtime_error("echec connection.");
}

void	Bot::_sendMessage(const std::string& message) const
{
	if (_socketFd == -1)
		return ;
	std::string	real_mess(message);
	if (message.find("\r\n") == std::string::npos)
		real_mess += "\r\n";
	ssize_t	bytesSent = send(_socketFd, real_mess.c_str(), real_mess.length(), 0);
	if (bytesSent == -1)
		std::cerr << "Error send : " << real_mess << std::endl;
	else
		std::cout << "Bot said -> " << real_mess;
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

	_last_bonjour = time(NULL);
	while (_isRunning)
	{
		if (time(NULL) - _last_bonjour > 60)
		{
			_last_bonjour = time(NULL);
			_sendMessage("WHO *");
		}
		std::memset(buffer, 0, sizeof(buffer));
		ssize_t	bytesReceived = recv(_socketFd, buffer, sizeof(buffer) - 1, 0);

		if (bytesReceived == 0)
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

void	Bot::_call_funcs(std::string func, const std::vector<std::string>& args, const std::string& nick)
{
	std::string levels[5] = {
		"JOIN",
		"PRIVMSG",
		"MODE",
		"INVITE",
		"352"
	};
	void (Bot::*f[5])(const std::vector<std::string>& args, const std::string& nick) = {
		&Bot::_PrivMsg_bot,
		&Bot::_PrivMsg_bot,
		&Bot::_Mode_bot,
		&Bot::_Invite_bot,
		&Bot::_Who_bot
	};
	for (int i = 0; i < 5; i++)
	{
		if (levels[i] == func)
			(this->*f[i])(args, nick);
	}
}

void	Bot::_processMessage(const std::string& message)
{
	if (message.empty())
		return;

	bool	end_param = false;
	std::string			end_string;
	std::istringstream			iss(message);
	std::string					word;
	std::vector<std::string>	args;
	while (iss >> word)
	{
		if (!word.empty() && !end_param && word[0] == ':' && args.size() != 0)
		{
			word.erase(0, 1);
			end_param = true;
		}
		if (end_param)
		{
			if (!end_string.empty())
				end_string += " ";
			end_string += word;
		}
		else
			args.push_back(word);
	}
	if (end_param == true)
		args.push_back(end_string);
	if (args.empty())
		return;
	std::string cmd = args[1];
	size_t pos = args[0].find('!');
	std::string	nick = args[0].substr(1, pos - 1);
	args.erase(args.begin());
	args.erase(args.begin());
	_call_funcs(cmd, args, nick);
}

void	Bot::_Who_bot(const std::vector<std::string>& args, const std::string& nick)
{
	(void)nick;
	if (args.size() < 6)
		return ;
	std::string	nick_check = args[5];
	if (nick_check == _nickname)
		return ;
	for (std::vector<std::string>::iterator it = _bonjourUsers.begin(); it != _bonjourUsers.end();  it++)
	{
		if (*it == nick_check)
			return ;
	}
	_bonjourUsers.push_back(nick_check);
	_sendbonjour_client(nick_check);
}

void	Bot::_sendbonjour_client(const std::string& targetUser)
{
	std::string	msg = "PRIVMSG " + targetUser + " :HI i m " + _nickname + " the bot\n"
		+ "Add me on your channel with the INVITE command\n"
		+ "I can do multiple fun command and if i am an operator on the channel i kick people"
		+ " if they say a curse word";
	_sendMessage(msg);
}

void	Bot::_PrivMsg_bot(const std::vector<std::string>& args, const std::string& nick)
{
	std::string	msg_recv;
	
	if (args.empty())
		return ;
	std::cout << "prv" << args[1] << std::endl;
	std::string target(args[0]);
	msg_recv = args[1];
	if (msg_recv.substr(0, 1) != "!")
		return ;
	msg_recv.erase(0, 1);
	std::istringstream	iss(msg_recv);
	std::string			cmd;
	iss >> cmd;
	_botCommand(cmd, nick, target);
}

void	Bot::_botCommand(const std::string& cmd, const std::string& nick, const std::string& target)
{
	if (cmd == "random")
	{
		std::srand(NULL);
		int	rand = std::rand() % 101;
		if (rand != 42)
		{
			std::string	msg = "PRIVMSG " + target + " :" + nick + " failed with" + std::to_string(rand);
			_sendMessage(msg);
		}
		else
		{
			std::string	msg = "PRIVMSG " + target + " :" + nick + " won with" + std::to_string(rand);
			_sendMessage(msg);
		}
	}
	if (cmd == "help")
	{
		std::string	msg = "PRIVMSG " + target + " :Hi every one the bot " + _nickname + " joined here is a list of the cmd i can do :"
		+ "\n!help\n"
		+ "\n!random\n";
		_sendMessage(msg);
	}
}

void	Bot::_Invite_bot(const std::vector<std::string>& args, const std::string& nick)
{
	(void)nick;
	std::cout << "invite detected " << args[0] << args[1] << std::endl;
	if (args.size() < 2)
		return ;
	std::string	channel = args[1];
	
	std::string	msg = "JOIN " + args[1];
	_sendMessage(msg);
	_channelOp[args[1]] = false;
	_joinandintroduce(args[1]);
}

void	Bot::_joinandintroduce(const std::string& channel)
{
	std::string	msg = "PRIVMSG " + channel + " :Hi every one the bot " + _nickname + " joined here is a list of the cmd i can do :"
		+ "\n!help\n"
		+ "\n!random\n";
	_sendMessage(msg);
}

void	Bot::_Mode_bot(const std::vector<std::string>& args, const std::string& nick)
{
	(void)nick;
	if (args.size() < 3)
		return ;
	if (args[2] != _nickname)
		return ;
	if (_channelOp.find(args[0]) == _channelOp.end())
		return ;
	if (args[1] == "-o")
	{
		std::string	msg = "PRIVMSG " + args[0] + " :i can no more ban people ....";
		_sendMessage(msg);
		_channelOp[args[0]] = false;
	}
	else if (args[1] == "+o")
	{
		std::string	msg = "PRIVMSG " + args[0] + " :i can now ban people if they say a curse word....";
		_sendMessage(msg);
		_channelOp[args[0]] = true;
	}
}