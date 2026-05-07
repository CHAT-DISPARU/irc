#include "NickCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

bool	Channel::get_mode(char c)
{
	if (c == 'i')
		return mode[0];
	if (c == 't')
		return mode[1];
	if (c == 'k')
		return mode[2];
	if (c == 'o')
		return mode[3];
	if (c == 'l')
		return mode[4];
	return false;
}

void	Channel::set_mode(char c, bool status)
{
	if (c == 'i')
		mode[0] == status;
	if (c == 't')
		mode[1] == status;
	if (c == 'k')
		mode[2] == status;
	if (c == 'o')
		mode[3] == status;
	if (c == 'l')
		mode[4] == status;
}

void	Channel::addMember(Client *client)
{
	this->members[client->get_fd()] = new Client(client->get_fd());
}

void	Channel::addOperator(Client *client)
{
	this->operators[client->get_fd()] = new Client(client->get_fd());
}

void	Channel::delMember(Client *client)
{
	delete members[client->get_fd()];
}

void	Channel::delOperator(Client *client)
{
	delete operators[client->get_fd()];
}

void	Channel::set_topic(const std::string& str)
{
	_topic = str;
}

const std::string&	Channel::get_topic()
{
	return _topic;
}
