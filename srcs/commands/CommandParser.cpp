/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:49:49 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/06 15:09:40 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandParser.hpp"
#include "Server.hpp"
#include "PassCommand.hpp"
#include "NickCommand.hpp"
#include "UserCommand.hpp"

CommandParser::CommandParser()
{
	_commands["PASS"] = new PassCommand();
	_commands["NICK"] = new NickCommand();
	_commands["USER"] = new UserCommand();
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
			end_string += word;
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
