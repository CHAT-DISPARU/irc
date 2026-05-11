/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CapCommand.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 18:33:42 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/11 21:21:21 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CapCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	CapCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	(void)server;
	if (args.empty())
		return;
	std::string msg;

	if (args[0] == "LS")
		msg = ":server CAP * LS :\r\n";
	else if (args[0] == "REQ")
		msg = ":server CAP * NAK :" + (args.size() > 1 ? args[1] : "") + "\r\n";
	else if (args[0] == "END")
		return ;
	if (!msg.empty())
		client->add_to_sendBuff(msg);
}
