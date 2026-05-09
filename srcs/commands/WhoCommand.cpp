/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoCommand.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 18:39:55 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/09 12:12:38 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WhoCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void	WhoCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->isAuthenticated(client) || !server->checkRegistration(client))
		return;

	std::string	nick = client->get_nick_or_star();
	std::string	mask = (args.empty()) ? "*" : args[0];

	if (!mask.empty() && (mask[0] == '#' || mask[0] == '&'))
	{
		Channel* channel = server->getChannel(mask);
		if (!channel)
		{
			server->sendReply(client->get_fd(), "315", nick, mask + " :End of /WHO list");
			return;
		}
		
		std::map<int, Client*> members = channel->getMembers();
		for (std::map<int, Client*>::iterator it = members.begin(); it != members.end(); ++it)
		{
			Client*		member = it->second;
			std::string	prefix = channel->isOperator(member) ? "@" : "";

			server->sendReply(client->get_fd(), "352", nick, mask + " "
				+ member->get_user() + " " + member->get_ip() + " " + "server "
				+ member->get_nick() + " H" + prefix
				+ " :0 " + member->get_real());
		}
	}
	else
	{
		if (mask == "*")
		{
			const std::map<int, Client*>&	all_clients = server->getClients();

			for (std::map<int, Client*>::const_iterator it = all_clients.begin(); it != all_clients.end(); ++it)
			{
				Client* target = it->second;

				server->sendReply(client->get_fd(), "352", nick, "* " + target->get_user() + " " + 
					target->get_ip() + " " + "server " + 
					target->get_nick() + " H :0 " + target->get_real());
			}
		}
		else
		{
			Client* target = server->getClientByNick(mask);

			if (target)
			{
				server->sendReply(client->get_fd(), "352", nick, "* " + target->get_user() + " " + target->get_ip()
					+ " " + "server " + target->get_nick()
					+ " H :0 " + target->get_real());
			}
		}
	}
	server->sendReply(client->get_fd(), "315", nick, mask + " :End of /WHO list");
}
