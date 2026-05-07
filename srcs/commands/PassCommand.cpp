/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:37:55 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/07 12:05:11 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	PassCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (server->isAuthenticated(client))
	{
		server->sendReply(client->get_fd(), "462", client->get_nick_or_star(), ":You may not reregister");
		return ;
	}
	if (!server->hasEnoughParams(client, "PASS", args, 1))
		return;
	if (args[0] == server->getPassword())
		client->set_auth(true);
	else
		server->sendReply(client->get_fd(), "464", client->get_nick_or_star(), ":Password incorrect");
}
