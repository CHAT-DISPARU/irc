/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:30:05 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/05 19:41:41 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class	PassCommand : public ICommand
{
	public:
		PassCommand() {}
		~PassCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};