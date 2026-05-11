#include "TopicCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void	TopicCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
	if (!server->isAuthenticated(client) || !server->checkRegistration(client))
		return ;

	if (args.empty())
	{
		server->sendReply(client->get_fd(), "461", client->get_nick_or_star(), "TOPIC :Not enough parameters");
		return ;
	}

	std::string channelName = args[0];
	Channel* channel = server->getChannel(channelName);
	if (!channel)
	{
		server->sendReply(client->get_fd(), "403", client->get_nick_or_star(), channelName + " :No such channel");
		return ;
	}

	if (!channel->is_inChannel(client))
	{
		server->sendReply(client->get_fd(), "442", client->get_nick_or_star(), channelName + " :You're not on that channel");
		return ;
	}
	if (args.size() == 1)
	{
		if (channel->getTopic().empty())
			server->sendReply(client->get_fd(), "331", client->get_nick_or_star(), channelName + " :No topic is set");
		else
			server->sendReply(client->get_fd(), "332", client->get_nick_or_star(), channelName + " :" + channel->getTopic());
		return ;
	}
	std::string	topic = args[1];
	if (channel->hasMode('t') && !channel->isOperator(client))
	{
		server->sendReply(client->get_fd(), "482", client->get_nick_or_star(), args[0] + " :You're not channel operator");
		return ;
	}
	std::string joinMsg = ":" + client->get_nick_or_star() + "!" + client->get_user() + "@" + client->get_ip() + " TOPIC " + channelName + " :" + topic + "\r\n";
	channel->broadcast(joinMsg);
	channel->setTopic(topic);
}
