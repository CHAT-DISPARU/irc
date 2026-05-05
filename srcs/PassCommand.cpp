/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:37:55 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/05 18:54:50 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	PassCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (client->is_auth())
	{
		server->sendReply(client->get_fd(), "462", "*", ":already registered");
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
