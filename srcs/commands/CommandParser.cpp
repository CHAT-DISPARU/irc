/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:49:49 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/09 15:30:08 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandParser.hpp"
#include "Server.hpp"
#include "PassCommand.hpp"
#include "NickCommand.hpp"
#include "UserCommand.hpp"
#include "PrivmsgCommand.hpp"
#include "PongCommand.hpp"
#include "PingCommand.hpp"
#include "QuitCommand.hpp"
#include "JoinCommand.hpp"
#include "PartCommand.hpp"
#include "WhoCommand.hpp"
#include "WhoisCommand.hpp"
#include "CapCommand.hpp"
#include "InviteCommand.hpp"
#include "ModeCommand.hpp"
#include "KickCommand.hpp"

CommandParser::CommandParser()
{
	_commands["PASS"] = new PassCommand();
	_commands["NICK"] = new NickCommand();
	_commands["USER"] = new UserCommand();
	_commands["PRIVMSG"] = new PrivmsgCommand();
	_commands["PONG"] = new PongCommand();
	_commands["PING"] = new PingCommand();
	_commands["QUIT"] = new QuitCommand();
	_commands["JOIN"] = new JoinCommand();
	_commands["PART"] = new PartCommand();
	_commands["CAP"] = new CapCommand();
	_commands["WHO"] = new WhoCommand();
	_commands["WHOIS"] = new WhoisCommand();
	_commands["INVITE"] = new InviteCommand();
	_commands["KICK"] = new KickCommand();
	_commands["MODE"] = new ModeCommand();
}

CommandParser::~CommandParser()
{
	for (std::map<std::string, ICommand*>::iterator it = _commands.begin(); it != _commands.end(); ++it)
		delete it->second;
}

void	CommandParser::Parse(Server* server, Client* client, const std::string& message)
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
		if (!word.empty() && word[0] == ':')
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
	std::string cmd = args[0];
	args.erase(args.begin());
	if (_commands.find(cmd) != _commands.end())
		_commands[cmd]->exec(server, client, args);
	else
	{
		std::cout << "Commande inconnue : " << cmd << std::endl;
		server->sendReply(client->get_fd(), "421", client->get_nick().empty() ? "*" : client->get_nick(), cmd + " :Unknown command");
	}
}
