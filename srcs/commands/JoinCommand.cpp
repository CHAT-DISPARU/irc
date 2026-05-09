/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:21:58 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/09 15:16:38 by gajanvie         ###   ########.fr       */
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

	std::string nick = client->get_nick_or_star();

	if (args.empty())
	{
		server->sendReply(client->get_fd(), "461", nick, "JOIN :Not enough parameters");
		return;
	}
	if (args[0] == "0")
	{
		std::vector<Channel*> joined = server->getClientChannels(client);
		for (std::vector<Channel*>::iterator it = joined.begin(); it != joined.end(); ++it)
		{
			Channel*	chan = *it;
			std::string	partMsg = ":" + nick + "!" + client->get_user() + "@" + client->get_ip()
								+ " PART " + chan->getName() + " :Left all channels\r\n";
			chan->broadcast(partMsg);
			if (chan->isOperator(client))
				chan->removeOperator(client->get_fd());
			chan->removeMember(client->get_fd());
			if (chan->isEmpty())
				server->removeChannel(chan->getName());
		}
		return ;
	}
	std::vector<std::string>	channels;
	std::vector<std::string>	keys;
	std::stringstream			ssChan(args[0]);
	std::string					token;

	while (getline(ssChan, token, ','))
		channels.push_back(token);
	if (args.size() > 1)
	{
		std::stringstream ssKey(args[1]);
		while (getline(ssKey, token, ','))
			keys.push_back(token);
	}
	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string	channelName = channels[i];
		std::string	key = (i < keys.size()) ? keys[i] : "";

		if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
		{
			server->sendReply(client->get_fd(), "403", nick, channelName + " :No such channel");
			continue;
		}
		Channel*	channel = server->getChannel(channelName);
		if (channel && channel->is_inChannel(client))
			continue;
		if (channel == NULL)
		{
			channel = new Channel(channelName);
			server->addChannel(channel);
			channel->addMember(client);
			channel->addOperator(client);
		}
		else
		{
			if (channel->hasMode('i') && !channel->isInvited(client->get_fd()))
			{
				server->sendReply(client->get_fd(), "473", nick, channelName + " :Cannot join channel (+i)");
				continue;
			}
			if (channel->hasMode('k') && !channel->checkKey(key))
			{
				server->sendReply(client->get_fd(), "475", nick, channelName + " :Cannot join channel (+k)");
				continue;
			}
			if (channel->hasMode('l') && channel->isFull())
			{
				server->sendReply(client->get_fd(), "471", nick, channelName + " :Cannot join channel (+l)");
				continue;
			}
			channel->addMember(client);
			channel->removeInvite(client->get_fd());
		}
		std::string	joinMsg = ":" + nick + "!" + client->get_user() + "@" + client->get_ip() + " JOIN :" + channelName + "\r\n";
		channel->broadcast(joinMsg);
		if (!channel->getTopic().empty())
			server->sendReply(client->get_fd(), "332", nick, channelName + " :" + channel->getTopic());
		else
			server->sendReply(client->get_fd(), "331", nick, channelName + " :No topic is set");
		std::string namesList = channel->getClientList();
		server->sendReply(client->get_fd(), "353", nick, "= " + channelName + " :" + namesList);
		server->sendReply(client->get_fd(), "366", nick, channelName + " :End of /NAMES list");
	}
}
