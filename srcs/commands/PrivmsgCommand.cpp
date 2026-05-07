/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:11:50 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/07 13:53:09 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivmsgCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	PrivmsgCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->checkRegistration(client))
		return ;
	if (args.empty())
	{
		server->sendReply(client->get_fd(), "411", client->get_nick(), ":No recipient given (PRIVMSG)");
		return ;
	}
	if (args.size() < 2 || args[1].empty())
	{
		server->sendReply(client->get_fd(), "412", client->get_nick(), ":No text to send");
		return ;
	}

	std::string target  = args[0];
	std::string message = args[1];
	Client* dest = NULL;
	try
	{
		dest = server->getClientByNick(target);
	}
	catch (const std::exception&)
	{
		server->sendReply(client->get_fd(), "401", client->get_nick(), target + " :No such nick");
		return ;
	}
	dest->add_to_sendBuff(":" + client->get_nick() + "!" + client->get_user() + "@" + client->get_ip() + " PRIVMSG " + target + " :" + message + "\r\n");
}