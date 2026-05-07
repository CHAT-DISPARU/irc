/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolavale <rolavale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:05:31 by gajanvie          #+#    #+#             */
/*   Updated: 2026/05/07 16:49:58 by rolavale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	Server::disconect_client(int fd)
{
	close (fd);
	std::cout << RED << "the client : FD [" << fd << "] disconnected" << RESET << std::endl;
	delete this->clients[fd];
	clients.erase(fd);
	
	for (std::vector <struct pollfd>::iterator it = pollfd.begin(); it != pollfd.end(); it++)
	{
		if (it->fd == fd)
		{
			pollfd.erase(it);
			return ;
		}
	}
}


bool	Server::signal = false;
void	Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << std::endl << "Signal recv" << std::endl;
	Server::signal = true;
}

void	Server::SerSocket()
{
	this->fdsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fdsocket < 0)
		throw (std::runtime_error("error : Socket Creation"));
	if (fcntl(this->fdsocket, F_SETFL, O_NONBLOCK) == -1)
		throw (std::runtime_error("error : fcntl"));
	int	opt = 1;
	if (setsockopt(fdsocket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) == -1)
		throw (std::runtime_error("error : Socket option"));
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(fdsocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		throw (std::runtime_error("error : Socket bind"));
	if (listen(fdsocket, SOMAXCONN) == -1)
		throw (std::runtime_error("error : Socket listen"));
}

void	Server::ServerInit(int port, std::string password)
{
	this->port = port;
	this->_password = password;
	SerSocket();
}

void	Server::AcceptNewClient()
{
	struct sockaddr_in	addr;
	socklen_t len = sizeof(addr);
	int				new_client_fd;

	new_client_fd = accept(this->fdsocket, (struct sockaddr *)&addr, &len);
	if (new_client_fd == -1)
	{
		std::cerr << "Error : Accept new Client" << std::endl;
		return ;
	}
	if (fcntl(new_client_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "Error : fcntl new Client" << std::endl;
		return ;
	}
	std::string client_ip = inet_ntoa(addr.sin_addr);
	struct pollfd pollfd_server;

	pollfd_server.fd = new_client_fd;
	pollfd_server.events = POLLIN;
	pollfd_server.revents = 0;
	this->pollfd.push_back(pollfd_server);
	std::cout << GREEN << "New Client FD : [" << new_client_fd << "]" << RESET << std::endl;
	this->clients[new_client_fd] = new Client(new_client_fd);
	this->clients[new_client_fd]->set_ip(client_ip);
}

void	Server::ReceiveNewData(int fd)
{
	char	buffer[1024];
	ssize_t	byte_r;
	
	std::memset(buffer, 0, sizeof(buffer));
	byte_r = recv(fd, buffer, sizeof(buffer) - 1, 0);
	if (byte_r <= 0)
	{
		if (byte_r < 0)
		{
			std::cerr << "Error : read Client" << std::endl;
			return ;
		}
		else
			disconect_client(fd);
		return ;
	}
	std::string	data(buffer);
	this->clients[fd]->add_to_buff(data);
	this->clients[fd]->set_last_activity(time(NULL));
	this->clients[fd]->set_ping_sent(false);
	std::string buff = this->clients[fd]->get_buff();
	size_t	pos = buff.find("\r\n");
	while (pos != std::string::npos)
	{
		std::string line = buff.substr(0, pos);
		this->clients[fd]->EraseLine(pos + 2);
		this->_parser.Parse(this, this->clients[fd], line);
		if (this->clients.find(fd) == this->clients.end())
			return;
		buff = this->clients[fd]->get_buff();
		pos = buff.find("\r\n");
	}
}


void	Server::run(void)
{	
	struct pollfd pollfd_server;
	
	pollfd_server.fd = fdsocket;
	pollfd_server.events = POLLIN;
	pollfd_server.revents = 0;
	this->pollfd.push_back(pollfd_server);
	std::cout << "Waiting client ..." << std::endl;
	while (Server::signal == false)
	{
		for (size_t i = 0; i < pollfd.size(); i++)
		{
			if (pollfd[i].fd != fdsocket)
			{
				int	fd = pollfd[i].fd;
				if (clients[fd]->hasDataToSend())
					pollfd[i].events = POLLIN | POLLOUT; // lire et ecrire
				else
					pollfd[i].events = POLLIN; // que lre
			}
		}
		if (poll(&pollfd[0], pollfd.size(), -1) == -1)
		{
			if (Server::signal == false)
				throw(std::runtime_error("poll() faild"));
			else
				return ;
		}
		for (size_t i = 0; i < pollfd.size(); i++)
		{
			if (pollfd[i].revents & POLLIN)
			{
				if (pollfd[i].fd == this->fdsocket)
					AcceptNewClient();
				else
					ReceiveNewData(pollfd[i].fd);
			}
			if (pollfd[i].revents & POLLOUT)
				SendData(pollfd[i].fd);
		}
	}
}

Server::~Server()
{
	for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		close(it->first);
		delete it->second;
	}
	clients.clear();
	pollfd.clear();
	if (fdsocket != -1)
	{
		close(fdsocket);
		fdsocket = -1;
	}
}

void	Server::sendReply(int fd, const std::string& code, const std::string& target, const std::string& message)
{
	// :<name_serv> <code_num> <target> :<explication>\r\n"
	std::string full_msg = ":gajanvie.rolavale.irc " + code + " " + target + " " + message + "\r\n";
	if (clients.find(fd) != clients.end())
		clients[fd]->add_to_sendBuff(full_msg);
}

void	Server::SendData(int fd)
{
	Client*		client = clients[fd];
	std::string	data = client->get_sendBuff();

	ssize_t bytes_sent = send(fd, data.c_str(), data.length(), 0);
	if (bytes_sent < 0)
	{
		// buffer os plein pas grave prochain poll
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return; 
		std::cerr << "Erreur d'envoi au FD [" << fd << "] -> deconnexion" << std::endl;
		disconect_client(fd);
	} 
	else if (bytes_sent > 0)
		client->erase_sendBuff(bytes_sent);
}

Client*		Server::getClientByNick(const std::string& nick)
{
	for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second->get_nick() == nick)
			return (it->second);
	}
	throw (std::exception());
}

bool		Server::checknickuse(const std::string& nick)
{
	try
	{
		getClientByNick(nick);
		return (true);
	}
	catch (const std::exception& e)
	{
		return (false);
	}
}

bool	Server::checkRegistration(Client* client)
{
	if (!client->is_complete())
	{
		sendReply(client->get_fd(), "451", client->get_nick_or_star(), ":You have not registered");
		return false;
	}
	return true;
}

bool	Server::alreadyRegistered(Client* client)
{
	if (client->is_complete())
	{
		sendReply(client->get_fd(), "462", client->get_nick_or_star(), ":You may not reregister");
		return true;
	}
	return false;
}

bool	Server::isAuthenticated(Client* client)
{
	if (client->is_auth()) 
		return true;
	return false;
}

bool	Server::hasEnoughParams(Client* client, const std::string& commandName, const std::vector<std::string>& args, size_t requiredSize)
{
	if (args.size() < requiredSize)
	{
		sendReply(client->get_fd(), "461", client->get_nick_or_star(), commandName + " :Not enough parameters");
		return false;
	}
	return true;
}

void	Server::sendWelcome(Client* client)
{
	std::string nick = client->get_nick();
	std::string user = client->get_user();
	std::string host = client->get_ip();;
	std::string network = nick + "!" + user + "@" + host;
	sendReply(client->get_fd(), "001", nick, ":Welcome to the Internet Relay Network " + network);
	sendReply(client->get_fd(), "375", nick, ":- gajanvie.rolavale.irc Message of the day -");
	sendReply(client->get_fd(), "372", nick, ":-  _          _ _         ");
	sendReply(client->get_fd(), "372", nick, "               ,,ggddY\"\"\"Ybbgg,,");
	sendReply(client->get_fd(), "372", nick, "          ,agd888b,_ \"Y8, ___`\"\"Ybga,");
	sendReply(client->get_fd(), "372", nick, "       ,gdP\"\"88888888baa,.\"\"8b    \"888g,");
	sendReply(client->get_fd(), "372", nick, "     ,dP\"     ]888888888P'  \"Y     `888Yb,");
	sendReply(client->get_fd(), "372", nick, "   ,dP\"      ,88888888P\"  db,       \"8P\"\"Yb,");
	sendReply(client->get_fd(), "372", nick, "  ,8\"       ,888888888b, d8888a           \"8,");
	sendReply(client->get_fd(), "372", nick, " ,8'        d88888888888,88P\"' a,          `8,");
	sendReply(client->get_fd(), "372", nick, ",8'         88888888888888PP\"  \"\"           `8,");
	sendReply(client->get_fd(), "372", nick, "d'          I88888888888P\"                   `b");
	sendReply(client->get_fd(), "372", nick, "8           `8\"88P\"\"Y8P'                      8");
	sendReply(client->get_fd(), "372", nick, "8            Y 8[  _ \"                        8");
	sendReply(client->get_fd(), "372", nick, "8              \"Y8d8b  \"Y a                   8");
	sendReply(client->get_fd(), "372", nick, "8                 `\"\"8d,   __                 8");
	sendReply(client->get_fd(), "372", nick, "Y,                    `\"8bd888b,             ,P");
	sendReply(client->get_fd(), "372", nick, "`8,                     ,d8888888baaa       ,8'");
	sendReply(client->get_fd(), "372", nick, " `8,                    888888888888'      ,8'");
	sendReply(client->get_fd(), "372", nick, "  `8a                   \"8888888888I      a8'");
	sendReply(client->get_fd(), "372", nick, "   `Yba                  `Y8888888P'    adP'");
	sendReply(client->get_fd(), "372", nick, "     \"Yba                 `888888P'   adY\"");
	sendReply(client->get_fd(), "372", nick, "       `\"Yba,             d8888P\" ,adP\"'  Welcome");
	sendReply(client->get_fd(), "372", nick, "          `\"Y8baa,      ,d888P,ad8P\"'           to");
	sendReply(client->get_fd(), "372", nick, "               ``\"\"YYba8888P\"\"''          Our IRC");
	sendReply(client->get_fd(), "376", nick, ":End of /MOTD command.");
}