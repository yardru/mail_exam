// "server" class header file
//
// Created by Yaroslav Drugov on 20.07.16
// as part of "server" project
//

#ifndef _SERVER_H_
#define _SERVER_H_

#include "handler.h"

class server_t
{
private:
    char ip[16];
    unsigned short port;
    std::vector<handler_t *> handlers;
    void session(psocket socket);

public:
    server_t();
    server_t(int argc, char **argv);
    handler_t * operator<<(handler_t *handler);
    void run();
};


#endif // _SERVER_H_
