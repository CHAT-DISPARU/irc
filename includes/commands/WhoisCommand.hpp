/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoisCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 19:00:37 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/08 19:13:47 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class	WhoisCommand : public ICommand
{
	public:
		WhoisCommand() {}
		~WhoisCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};
