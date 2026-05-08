/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 12:33:39 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/08 12:34:18 by CHAT-DISPAR      ###   ########.fr       */
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

	std::string	username = args[0];
	if (username.length() > USERLEN)
		username = username.substr(0, USERLEN);
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
	client->set_user(username);
	client->set_real(args[3]);
	if (!client->get_nick().empty())
	{
		client->set_complete(true);
		server->sendWelcome(client);
	}
}