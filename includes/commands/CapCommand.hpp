/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CapCommand.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 18:33:35 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/09 12:14:19 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class	CapCommand : public ICommand
{
	public:
		CapCommand() {}
		~CapCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};

