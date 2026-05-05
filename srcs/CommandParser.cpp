/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:49:49 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/05 19:41:34 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandParser.hpp"
#include "Server.hpp"
#include "PassCommand.hpp"

CommandParser::CommandParser()
{
	_commands["PASS"] = new PassCommand();
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

	std::istringstream			iss(message);
	std::string					word;
	std::vector<std::string>	args;
	while (iss >> word)
		args.push_back(word);
	if (args.empty())
		return;
	std::string cmd = args[0];
	args.erase(args.begin());
	if (_commands.find(cmd) != _commands.end())
		_commands[cmd]->exec(server, client, args);
	else
	{
		std::cout << "Commande nconnue : " << cmd << std::endl;
		server->sendReply(client->get_fd(), "421", "*", cmd + " :Unknown command");
	}
}
