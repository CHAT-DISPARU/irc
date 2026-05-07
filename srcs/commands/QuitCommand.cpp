/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:36:14 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/07 12:16:25 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "QuitCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	QuitCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	std::string user_id = client->get_nick_or_star();
	std::string reason = (args.empty()) ? "Leaving" : args[0];

	std::cout << RED << "Exit: [" << user_id << "] (FD: " << client->get_fd() << ") Reason: " << reason << RESET << std::endl;
	server->disconect_client(client->get_fd());
}