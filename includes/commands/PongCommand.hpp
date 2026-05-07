/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:35:17 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/07 11:36:00 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class   PongCommand : public ICommand
{
public:
	PongCommand() {}
	~PongCommand() {}
	void    exec(Server* server, Client* client, const std::vector<std::string>& args);
};