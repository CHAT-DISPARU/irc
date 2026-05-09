/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:19:33 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/09 14:19:44 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class	ModeCommand : public ICommand
{
	public:
		ModeCommand() {}
		~ModeCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};
