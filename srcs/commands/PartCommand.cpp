/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:44:30 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/08 15:01:50 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PartCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void	PartCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->isAuthenticated(client) || !server->checkRegistration(client))
		return;
	if (args.empty())
	{
		server->sendReply(client->get_fd(), "461", client->get_nick(), "PART :Not enough parameters");
		return;
	}

	std::stringstream	channels(args[0]);
	std::string			reason = (args.size() > 1) ? args[1] : "Leaving";
	std::string			channel;
	char				del = ',';

	while (getline(channels, channel, del))
	{
		Channel *channel_tmp = server->getChannel(channel);
		if (!channel_tmp)
		{
			server->sendReply(client->get_fd(), "403", client->get_nick_or_star(), channel + ":No such channel");
			return;
		}
		else
		{
			
		}
	}
	
}
