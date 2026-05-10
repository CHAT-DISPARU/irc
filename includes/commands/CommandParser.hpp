/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:49:12 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/10 19:13:02 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Client.hpp"
#include "ICommand.hpp"
class Server;
#include <map>
#include <string>
#include <vector>
#include <sstream>

class	CommandParser
{
	private:
		std::map<std::string, ICommand*> _commands;
	public:
		CommandParser();
		~CommandParser();
		void	Parse(Server* server, Client* client, const std::string& message);
};
