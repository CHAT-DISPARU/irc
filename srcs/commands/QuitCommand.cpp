/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:36:14 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/11 20:11:28 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "QuitCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

#include "QuitCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void	QuitCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	std::string				reason = (args.empty()) ? "Leaving" : args[0];
	std::string				quitMsg = ":" + client->get_nick_or_star() + "!" + client->get_user() + "@" + client->get_ip() + " QUIT :" + reason + "\r\n";
	std::vector<Channel*>	channels = server->getClientChannels(client);
	std::vector<int>		notified_fds;

	for (size_t i = 0; i < channels.size(); i++)
	{
		std::map<int, Client*>	members = channels[i]->getMembers();
		for (std::map<int, Client*>::iterator it = members.begin(); it != members.end(); ++it)
		{
			int		dest_fd = it->first;
			bool	already_notified = false;

			for (size_t j = 0; j < notified_fds.size(); j++)
			{
				if (notified_fds[j] == dest_fd)
				{
					already_notified = true;
					break ;
				}
			}
			if (dest_fd != client->get_fd() && !already_notified)
			{
				it->second->add_to_sendBuff(quitMsg);
				notified_fds.push_back(dest_fd);
			}
		}
	}

	std::cout << RED << "Exit: [" << client->get_nick_or_star() << "] (FD: " << client->get_fd() << ") Reason: " << reason << RESET << std::endl;
	server->disconect_client(client->get_fd());
}