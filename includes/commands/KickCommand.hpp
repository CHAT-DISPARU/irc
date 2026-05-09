/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:01:10 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/09 15:01:22 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class	KickCommand : public ICommand
{
	public:
		KickCommand() {}
		~KickCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};
