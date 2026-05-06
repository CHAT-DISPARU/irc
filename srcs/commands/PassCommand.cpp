/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:37:55 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/06 15:00:39 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	PassCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (client->is_auth())
	{
		server->sendReply(client->get_fd(), "462", client->get_nick().empty() ? "*" : client->get_nick(), ":You may not reregister");
		return;
	}
	if (args.empty())
	{
		server->sendReply(client->get_fd(), "461", "*", "PASS :Not enough parameters");
		return;
	}
	if (args[0] == server->getPassword())
		client->set_auth(true);
	else
	{
		server->sendReply(client->get_fd(), "464", "*", ":Password incorrect");
	}
}
