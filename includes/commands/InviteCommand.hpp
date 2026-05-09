/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 13:22:00 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/09 13:50:43 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICommand.hpp"

class   InviteCommand : public ICommand
{
public:
	InviteCommand() {}
	~InviteCommand() {}
	void    exec(Server* server, Client* client, const std::vector<std::string>& args);
};
