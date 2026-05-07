/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:36:08 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/07 11:44:08 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PongCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	PongCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (args.empty())
	{
		server->sendReply(client->get_fd(), "409", client->get_nick_or_star(), ":No origin specified");
		return;
	}

	std::string expected_token = "gajanvie.rolavale.irc";

	std::string received_token = args[0];
	if (received_token != expected_token)
	{
		std::cout << YELLOW << "Warning: Invalid PONG token from [" << client->get_nick_or_star() << "] (" << received_token << ")" << RESET << std::endl;
		return;
	}
	std::cout << GREEN << "Valid PONG received from [" << client->get_nick_or_star() << "]" << RESET << std::endl;
}