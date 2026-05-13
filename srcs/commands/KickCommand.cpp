/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:01:33 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/13 09:59:05 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KickCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void	KickCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->isAuthenticated(client) || !server->checkRegistration(client))
		return;

	std::string nick = client->get_nick_or_star();

	if (args.size() < 2)
	{
		server->sendReply(client->get_fd(), "461", nick, "KICK :Not enough parameters");
		return;
	}
	Channel *channel = server->getChannel(args[0]);
	if (!channel)
	{
		server->sendReply(client->get_fd(), "403", nick, args[0] + " :No such channel");
		return ;
	}
	if (!channel->is_inChannel(client))
	{
		server->sendReply(client->get_fd(), "442", nick, args[0] + " :You're not on that channel");
		return ;
	}
	if (!channel->isOperator(client))
	{
		server->sendReply(client->get_fd(), "482", nick, args[0] + " :You're not channel operator");
		return ;
	}
	std::vector<std::string>	users;
	std::stringstream			ssChan(args[1]);
	std::string					token;
	std::string					reason = "";

	while (getline(ssChan, token, ','))
		users.push_back(token);
	if (args.size() == 3)
		reason = args[2];
	for (size_t i = 0; i < users.size(); i++)
	{
		Client*		targetClient = server->getClientByNick(users[i]);

		if (!targetClient)
		{
			server->sendReply(client->get_fd(), "401", nick, users[i] + " :No such nick/channel");
			continue ;
		}
		if (!channel->is_inChannel(targetClient))
		{
			server->sendReply(client->get_fd(), "441", nick, targetClient->get_nick()
				+ " " + channel->getName() + " :They aren't on that channel");
			continue;
		}
		std::string	kickMsg = ":" + client->get_nick() + "!" + client->get_user()
			+ "@" + client->get_ip() + " KICK " + channel->getName() + " "
			+ targetClient->get_nick() + (reason.empty() ? "" : " :" + reason) + "\r\n";
		channel->broadcast(kickMsg);
		channel->removeMember(targetClient->get_fd());
		if (channel->isEmpty())
		{
			server->removeChannel(channel->getName());
			break ;
		}
	}
}
