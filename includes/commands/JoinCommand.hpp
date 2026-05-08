/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:21:40 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/08 12:37:39 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class	JoinCommand : public ICommand
{
	public:
		JoinCommand() {}
		~JoinCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};
