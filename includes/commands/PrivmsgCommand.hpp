#pragma once
#include "ICommand.hpp"

class   PrivmsgCommand : public ICommand
{
public:
    PrivmsgCommand() {}
    ~PrivmsgCommand() {}
    void    exec(Server* server, Client* client, const std::vector<std::string>& args);
};
