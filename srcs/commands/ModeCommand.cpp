/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:19:56 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/11 21:27:53 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModeCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void	ModeCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->isAuthenticated(client) || !server->checkRegistration(client))
		return;

	std::string nick = client->get_nick_or_star();
	if (!server->hasEnoughParams(client, "MODE", args, 1))
		return;
	std::string	target = args[0];
	if (target[0] == '#' || target[0] == '&')
	{
		Channel* channel = server->getChannel(target);
		if (!channel)
		{
			server->sendReply(client->get_fd(), "403", nick, target + " :No such channel");
			return;
		}
		if (args.size() == 1)
		{
			std::string	modes = "+";
			std::string	modeArgs = "";
			if (channel->hasMode('i'))
				modes += "i";
			if (channel->hasMode('t'))
				modes += "t";
			if (channel->hasMode('k'))
			{
				modes += "k";
				modeArgs += " *";
			}
			if (channel->hasMode('l'))
			{
				std::stringstream ss;
				ss << " " << channel->get_limit();
				modes += "l";
				modeArgs += ss.str();
			}
			server->sendReply(client->get_fd(), "324", nick, target + modes == "+" ? "" : (" " + modes + modeArgs));
			//a ajouter rpl 329 creation time
			server->sendReply(client->get_fd(), "329", nick, target + " :pas fait");
			return ;
		}
		if (!channel->isOperator(client))
		{
			server->sendReply(client->get_fd(), "482", nick, target + " :You're not channel operator");
			return ;
		}

		std::string	modestring = args[1];
		bool		adding = true;
		size_t		argIndex = 2;
		std::string	appliedModes = "";
		std::string	appliedArgs = "";
		char		currentSign = '+';

		for (size_t i = 0; i < modestring.size(); i++)
		{
			char c = modestring[i];

			if (c == '+')
			{
				adding = true;
				currentSign = '+';
				continue;
			}
			if (c == '-')
			{
				adding = false;
				currentSign = '-';
				continue;
			}
			if (c == 'o')
			{
				if (argIndex >= args.size())
					continue;
				std::string	targetNick = args[argIndex++];
				Client*		targetClient = server->getClientByNick(targetNick);
				if (!targetClient || !channel->is_inChannel(targetClient))
				{
					server->sendReply(client->get_fd(), "441", nick, targetNick + " " + target + " :They aren't on that channel");
					continue;
				}
				if (adding)
					channel->addOperator(targetClient);
				else
					channel->removeOperator(targetClient->get_fd());
				appliedModes += c;
				appliedArgs += " " + targetNick;
			}
			else if (c == 'k')
			{
				if (adding)
				{
					if (argIndex >= args.size())
						continue;
					std::string key = args[argIndex++];
					channel->setKey(key);
					channel->setMode('k', true);
					appliedModes += c;
					appliedArgs += " " + key;
				}
				else
				{
					channel->setKey("");
					channel->setMode('k', false);
					appliedModes += c;
				}
			}
			else if (c == 'l')
			{
				if (adding)
				{
					if (argIndex >= args.size())
						continue;
					size_t limit = std::strtol(args[argIndex++].c_str(), NULL, 10);
					if (limit <= 0)
						continue;
					channel->setLimit(limit);
					channel->setMode('l', true);
					appliedModes += c;
					appliedArgs += " " + args[argIndex - 1];
				}
				else
				{
					channel->setLimit(0);
					channel->setMode('l', false);
					appliedModes += c;
				}
			}
			else if (c == 'i' || c == 't')
			{
				channel->setMode(c, adding);
				appliedModes += c;
			}
			else
				server->sendReply(client->get_fd(), "501", nick, ":Unknown MODE flag");
		}
		if (!appliedModes.empty())
		{
			std::string modeMsg = ":" + nick + "!" + client->get_user() + "@" + client->get_ip()
				+ " MODE " + target + " " + currentSign + appliedModes
				+ appliedArgs + "\r\n";
			channel->broadcast(modeMsg);
		}
		return;
	}
	else
	{
		Client *client_param = server->getClientByNick(args[0]);
		if (!client_param)
		{
			server->sendReply(client->get_fd(), "401", client->get_nick(), args[0] + " :No such nick/channel");
			return ;
		}
		if (client_param != client)
		{
			server->sendReply(client->get_fd(), "502", client->get_nick(), ":Cant change mode for other users");
			return ;
		}
		if (args.size() == 1)
		{
			server->sendReply(client->get_fd(), "221", client->get_nick(), "");
			return ;
		}
		else
		{
			server->sendReply(client->get_fd(), "501", client->get_nick(), ":Unknown MODE flag");
			return ;
		}
	}
}
