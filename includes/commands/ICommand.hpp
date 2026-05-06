/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:33:19 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/06 14:12:38 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
class Server;
class Client;

class ICommand
{
	public:
		virtual ~ICommand() {}
		virtual void exec(Server* server, Client* client, const std::vector<std::string>& args) = 0;
};
