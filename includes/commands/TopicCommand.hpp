#pragma once
#include "ICommand.hpp"

class	TopicCommand : public ICommand
{
	public:
		TopicCommand() {}
		~TopicCommand() {}
		void	exec(Server* server, Client* client, const std::vector<std::string>& args);
};
