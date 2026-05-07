/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:10:08 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/07 11:35:54 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class   PingCommand : public ICommand
{
public:
	PingCommand() {}
	~PingCommand() {}
	void    exec(Server* server, Client* client, const std::vector<std::string>& args);
};