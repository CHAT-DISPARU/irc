/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:44:16 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/08 13:44:44 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class	PartCommand : public ICommand
{
	public:
		PartCommand() {}
		~PartCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};
