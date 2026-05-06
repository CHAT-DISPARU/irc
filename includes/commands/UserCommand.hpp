/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 12:33:24 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/06 14:37:31 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"
#define USERLEN 12

class	UserCommand : public ICommand
{
	public:
		UserCommand() {}
		~UserCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};
