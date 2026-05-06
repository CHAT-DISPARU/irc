/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:36:31 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/06 15:36:48 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class	QuitCommand : public ICommand
{
	public:
		QuitCommand() {}
		~QuitCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};
