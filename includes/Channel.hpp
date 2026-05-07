/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolavale <rolavale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:15:00 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/07 16:46:44 by rolavale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <Server.hpp>

class	Channel
{
	private:
		std::map<int, Client *>		members;
		std::map<int, Client *>		operators;
		bool						mode[5];
		std::string					_topic;
		std::string					_pass;
		size_t						user_limit;
		std::vector<int>			_invited_fd;
	public:
		bool				get_mode(char c);
		void				set_mode(char c, bool status);
		void				addMember(Client *client);
		void				addOperator(Client *client);
		void				delMember(Client *client);
		void				delOperator(Client *client);
		void				set_topic(const std::string& str);
		const std::string&	get_topic();
};
