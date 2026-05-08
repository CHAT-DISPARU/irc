/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:21:58 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/08 12:37:36 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void	JoinCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->isAuthenticated(client) || !server->checkRegistration(client))
		return;
	if (args.empty())
	{
		server->sendReply(client->get_fd(), "461", client->get_nick(), "JOIN :Not enough parameters");
		return;
	}

	std::string	channelName = args[0];
	std::string	key = (args.size() > 1) ? args[1] : "";
	if (channelName[0] != '#' && channelName[0] != '&')
	{
		server->sendReply(client->get_fd(), "403", client->get_nick(), channelName + " :No such channel");
		return;
	}

	Channel*	channel = server->getChannel(channelName);
	if (channel == NULL)
	{
		channel = new Channel(channelName);
		server->addChannel(channel);
		channel->addMember(client);
		channel->addOperator(client);
	}
	else
	{
		if (channel->hasMode('k') && !channel->checkKey(key))
		{
			server->sendReply(client->get_fd(), "475", client->get_nick(), channelName + " :Cannot join channel (+k)");
			return;
		}
		if (channel->hasMode('l') && channel->isFull())
		{
			server->sendReply(client->get_fd(), "471", client->get_nick(), channelName + " :Cannot join channel (+l)");
			return;
		}
		if (channel->hasMode('i') && !channel->isInvited(client->get_fd()))
		{
			server->sendReply(client->get_fd(), "473", client->get_nick(), channelName + " :Cannot join channel (+i)");
			return;
		}
		channel->addMember(client);
	}
	std::string joinMsg = ":" + client->get_nick() + "!" + client->get_user() + "@" + client->get_ip() + " JOIN :" + channelName + "\r\n";
	channel->broadcast(joinMsg);
	if (!channel->getTopic().empty())
		server->sendReply(client->get_fd(), "332", client->get_nick(), channelName + " :" + channel->getTopic());

	std::string namesList = channel->getClientList();
	server->sendReply(client->get_fd(), "353", client->get_nick(), "= " + channelName + " :" + namesList);
	server->sendReply(client->get_fd(), "366", client->get_nick(), channelName + " :End of /NAMES list");
}
