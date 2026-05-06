/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:49:12 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/06 14:12:42 by gajanvie         ###   ########.fr       */
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
