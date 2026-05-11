/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:11:50 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/11 20:05:44 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivmsgCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

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

	std::string	target = args[0];
	std::string	message = args[1];
	std::string	sender_prefix = ":" + client->get_nick() + "!" + client->get_user() + "@" + client->get_ip();

	if (target[0] == '#' || target[0] == '&')
	{
		Channel*	channel = server->getChannel(target);
		if (!channel)
		{
			server->sendReply(client->get_fd(), "401", client->get_nick(), target + " :No such nick/channel");
			return ;
		}
		if (!channel->is_inChannel(client))
		{
			server->sendReply(client->get_fd(), "404", client->get_nick(), target + " :Cannot send to channel");
			return ;
		}
		channel->broadcast(sender_prefix + " PRIVMSG " + target + " :" + message + "\r\n", client->get_fd());
	}
	else
	{
		Client*	dest = server->getClientByNick(target);
		if (!dest)
		{
			server->sendReply(client->get_fd(), "401", client->get_nick(), target + " :No such nick/channel");
			return ;
		}
		dest->add_to_sendBuff(sender_prefix + " PRIVMSG " + target + " :" + message + "\r\n");
	}
}