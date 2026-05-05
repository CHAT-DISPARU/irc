/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:33:19 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/05 19:41:43 by CHAT-DISPAR      ###   ########.fr       */
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