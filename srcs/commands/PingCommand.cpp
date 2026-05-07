/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:09:53 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/07 11:44:12 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PingCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	PingCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->checkRegistration(client))
		return;
	if (args.empty())
	{
		server->sendReply(client->get_fd(), "409", client->get_nick_or_star(), ":No origin specified");
		return;
	}

	std::string token = args[0];
	std::string pong_msg = ":gajanvie.rolavale.irc PONG gajanvie.rolavale.irc :" + token + "\r\n";
	
	client->add_to_sendBuff(pong_msg);
}
