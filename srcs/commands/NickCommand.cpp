/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:48:11 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/06 15:38:13 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	NickCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!client->is_auth())
	{
		server->sendReply(client->get_fd(), "464", "*", ":Password incorrect");
		return;
	}
	if (!client->get_nick().empty())
	{
		server->sendReply(client->get_fd(), "462", "*", ":You may not reregister");
		return;
	}
	if (args.empty())
	{
		server->sendReply(client->get_fd(), "431", "*", "No nickname given");
		return;
	}
	if (!client->checknick(args[0]))
	{
		server->sendReply(client->get_fd(), "432", "*", "Erroneus nickname");
		return;
	}
	if (server->checknickuse(args[0]))
	{
		server->sendReply(client->get_fd(), "433", "*", "Nickname is already in use");
		return;
	}
	client->set_nick(args[0]);
	if (!client->get_user().empty())
		client->set_complete(true);
}
