#include "PrivmsgCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"

void    PrivmsgCommand::exec(Server* server, Client* client, const std::vector<std::string>& args)
{
    //on verifie que le client est log
    if (!client->is_auth())
    {
        server->sendReply(client->get_fd(), "451", "*", ":You have not registered");
        return ;
    }
    //on verifie que le Client a bien mis "<target> :<message>" apres PRIVMSG
    if (args.empty())
    {
        server->sendReply(client->get_fd(), "411", client->get_nick(), ":No recipient given (PRIVMSG)");
        return ;
    }
    //s il n y a pas de message
    if (args.size() < 2 || args[1].empty())
    {
        server->sendReply(client->get_fd(), "412", client->get_nick(), ":No text to send");
        return ;
    }

    //target et message
    std::string target  = args[0];
    std::string message = args[1];
    //je recree un Client "fantome"
    Client* dest = NULL;
    //on le cherche
    try
    {
        dest = server->getClientByNick(target);
    }
    //erreur Client inexistant
    catch (const std::exception&)
    {
        server->sendReply(client->get_fd(), "401", client->get_nick(), target + " :No such nick");
        return ;
    }
    /*
    alors ici "pb" leger :
    je suis obligee d utiliser cette formulation car c est la norme du rfc 1459
    mais a la place du client->get_real
    je devrais avoir un client->get_host()
    hors le hostname est defini tel que * donc je sais pas trop quoi mettre
    */
    dest->add_to_sendBuff(":" + client->get_nick() + "!" + client->get_user() + "@" + client->get_real() + " PRIVMSG " + target + " :" + message + "\r\n");
}