/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:36:14 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/06 15:38:27 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "QuitCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	QuitCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!client->is_complete())
	{
		server->sendReply(client->get_fd(), "464", !client->get_nick().empty() ? client->get_nick() : "*", ":Password incorrect");
		return;
	}
	if (!client->get_user().empty())
	{
		server->sendReply(client->get_fd(), "462", !client->get_nick().empty() ? client->get_nick() : "*", ":You may not reregister");
		return;
	}
	if (args.empty() || args.size() < 4)
	{
		server->sendReply(client->get_fd(), "461", !client->get_nick().empty() ? client->get_nick() : "*", ":Not enough parameters");
		return;
	}
	if (args[1] != "0")
	{
		server->sendReply(client->get_fd(), "400", !client->get_nick().empty() ? client->get_nick() : "*", ":Please enter 0 for the second param of USER");
		return;
	}
	if (args[2] != "*")
	{
		server->sendReply(client->get_fd(), "400", !client->get_nick().empty() ? client->get_nick() : "*", ":Please enter * for the third param of USER");
		return;
	}
	if (args.size() >= 5)
	{
		server->sendReply(client->get_fd(), "400", !client->get_nick().empty() ? client->get_nick() : "*", ":Please enter : at the beginning of the fourth param");
		return;
	}
	client->set_real(args[3]);
	client->set_user(args[0]);
}
