/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CHAT-DISPARU <CHAT-DISPARU@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:15:00 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/08 18:39:14 by CHAT-DISPAR      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <Server.hpp>

class Channel
{
	private:
		std::string					_name;
		std::string					_topic;
		std::string					_pass;
		size_t						_user_limit;
		bool						_modes[5];
		std::map<int, Client *>		_members;
		std::map<int, Client *>		_operators;
		std::vector<int>			_invited_fds;

	public:
		Channel(std::string name);
		~Channel();

		std::string				getClientList();
		const std::string&		getName() const;
		const std::string&		getTopic() const;
		std::map<int, Client*>	getMembers() const;

		bool				hasMode(char c) const;
		bool				isFull() const;
		bool				isInvited(int fd) const;
		bool				checkKey(const std::string& key) const;
		bool				isEmpty() const;

		void				removeInvite(int fd);
		void				addMember(Client *client);
		void				removeMember(int fd);
		void				addOperator(Client *client);
		void				removeOperator(int fd);
		void				addInvite(int fd);
		bool				is_inChannel(Client *client);
		bool				isOperator(Client *client);
		
		void				broadcast(const std::string& message, int excludeFd = -1);

		void				setTopic(const std::string& topic);
		void				setMode(char c, bool status);
		void				setKey(const std::string& key);
		void				setLimit(size_t limit);
};
