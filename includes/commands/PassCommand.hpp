/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:30:05 by CHAT-DISPAR       #+#    #+#             */
/*   Updated: 2026/05/06 14:12:33 by gajanvie         ###   ########.fr       */
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
