/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 12:33:39 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/07 12:15:39 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	UserCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->isAuthenticated(client))
		return;
	if (server->alreadyRegistered(client))
		return;
	if (!server->hasEnoughParams(client, "USER", args, 4))
		return;

	if (args[1] != "0")
	{
		server->sendReply(client->get_fd(), "400", client->get_nick_or_star(), ":Please enter 0 for the second param of USER");
		return;
	}
	if (args[2] != "*")
	{
		server->sendReply(client->get_fd(), "400", client->get_nick_or_star(), ":Please enter * for the third param of USER");
		return;
	}
	if (args.size() >= 5)
	{
		server->sendReply(client->get_fd(), "400", client->get_nick_or_star(), ":Please enter : at the beginning of the fourth param");
		return;
	}
	client->set_user(args[0]);
	client->set_real(args[3]);
	if (!client->get_nick().empty())
	{
		client->set_complete(true);
		server->sendWelcome(client);
	}
}