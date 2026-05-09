/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 13:23:54 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/09 13:58:50 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InviteCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void	InviteCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->isAuthenticated(client) || !server->checkRegistration(client))
		return;

	std::string nick = client->get_nick_or_star();
	if (!server->hasEnoughParams(client, "INVIT", args, 2))
		return;
	Client	*client_to_inv = server->getClientByNick(args[0]);
	Channel	*channel_to_inv = server->getChannel(args[1]);
	if (!channel_to_inv)
	{
		server->sendReply(client->get_fd(), "403", nick, args[1] + " :No such channel");
		return ;
	}
	if (!channel_to_inv->is_inChannel(client))
	{
		server->sendReply(client->get_fd(), "442", nick, args[1] + " :You're not on that channel");
		return ;
	}
	if (!client_to_inv)
	{
		server->sendReply(client->get_fd(), "401", client->get_nick_or_star(), args[0] + " :No such nick/channel");
		return ;
	}
	if (channel_to_inv->hasMode('i') && !channel_to_inv->isOperator(client))
	{
		server->sendReply(client->get_fd(), "482", nick, args[1] + " :You're not channel operator");
		return ;
	}
	if (channel_to_inv->is_inChannel(client_to_inv))
	{
		server->sendReply(client->get_fd(), "443", nick, args[0] + " " + args[1] + " :is already on channel");
		return ;
	}
	std::string	sender_prefix = ":" + client->get_nick() + "!" + client->get_user() + "@" + client->get_ip();

	channel_to_inv->addInvite(client_to_inv->get_fd());
	server->sendReply(client->get_fd(), "341", nick, args[0] + " " + args[1] + " :Invite successful");
	client_to_inv->add_to_sendBuff(sender_prefix + " INVITE " + args[0] + " " + args[1] + "\r\n");
}
