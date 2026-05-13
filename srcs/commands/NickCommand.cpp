/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:48:11 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/13 10:00:10 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	NickCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->isAuthenticated(client))
		return;
	if (args.empty())
	{
		server->sendReply(client->get_fd(), "431", client->get_nick_or_star(), "No nickname given");
		return;
	}
	if (!client->checknick(args[0]))
	{
		server->sendReply(client->get_fd(), "432", client->get_nick_or_star(), "Erroneus nickname");
		return;
	}
	if (server->checknickuse(args[0]))
	{
		server->sendReply(client->get_fd(), "433", client->get_nick_or_star(), "Nickname is already in use");
		return;
	}
	client->set_nick(args[0]);
	if (!client->get_user().empty() && !client->is_complete())
	{
		client->set_complete(true);
		server->sendWelcome(client);
	}
}
