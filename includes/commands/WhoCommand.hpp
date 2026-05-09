/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoCommand.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 18:40:08 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/08 19:13:49 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class	WhoCommand : public ICommand
{
	public:
		WhoCommand() {}
		~WhoCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};
