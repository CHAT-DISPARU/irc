/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:47:36 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/06 10:48:04 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class	NickCommand : public ICommand
{
	public:
		NickCommand() {}
		~NickCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};
