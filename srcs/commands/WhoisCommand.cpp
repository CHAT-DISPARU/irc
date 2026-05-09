/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoisCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 19:00:56 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/09 12:12:34 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WhoisCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	WhoisCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->isAuthenticated(client) || !server->checkRegistration(client))
		return;
	if (args.empty())
	{
		server->sendReply(client->get_fd(), "431", client->get_nick_or_star(), ":No nickname given");
		return;
	}

	std::string	target_nick = args[0];
	Client*		target = server->getClientByNick(target_nick);

	if (!target)
	{
		server->sendReply(client->get_fd(), "401", client->get_nick_or_star(), target_nick + " :No such nick/channel");
		return;
	}
	std::string nick = client->get_nick_or_star();

	server->sendReply(client->get_fd(), "311", nick, target->get_nick() + " " + target->get_user() + " " + target->get_ip() + " * :" + target->get_real());
	server->sendReply(client->get_fd(), "312", nick, target->get_nick() + " " + "server_name" + " :Server Info");
	server->sendReply(client->get_fd(), "318", nick, target->get_nick() + " :End of /WHOIS list");
}
