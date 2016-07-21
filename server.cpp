// "server" class source file
//
// Created by Yaroslav Drugov on 20.07.16
// as part of "server" project
//

#include "server.h"

void server_t::session(psocket socket)
{
    streambuf request, response;
    std::istream is(&request);
    std::ostream os(&response);

    read_until(*socket, request, "\n");

    std::string str;
    is >> str;
    for (int i = 0; i < handlers.size(); i++)
    {
        if (handlers[i]->method == str)
        {
            (*handlers[i])(is, os);
            os.flush();
            write(*socket, response);
            break;
        }
    }
}

server_t::server_t() : port(12345)
{
    strcpy(ip, "127.0.0.1");
}

server_t::server_t(int argc, char **argv)
{
    const char opts[] = "h:p:d:";

    for (int i = 0; i < 3; i++)
        switch (getopt(argc, argv, opts))
        {
            case 'h':
                strcpy(ip, optarg);
                break;
            case 'p':
                sscanf(optarg, "%hu", &port);
                break;
            case 'd':
                chdir(optarg);
                break;
            default:
                exit(1);
        }
}

handler_t * server_t::operator<<(handler_t *handler)
{
    for (int i = 0; i < handlers.size(); i++)
        if (handlers[i]->method == handler->method)
        {
            handler_t *prev = handlers[i];
            handlers[i] = handler;
            return prev;
        }

    handlers.push_back(handler);

    return nullptr;
}

void server_t::run()
{
    io_service service;
    try
    {
        ip::tcp::endpoint endpoint(ip::address::from_string(ip), port);
        ip::tcp::acceptor acceptor(service, endpoint);
        while (1)
        {
            psocket socket = psocket(new ip::tcp::socket(service));
            acceptor.accept(*socket);
            boost::thread(boost::bind(&server_t::session, this, socket));
        }
    }
    catch (boost::system::system_error error)
    {
        fprintf(stderr, "error: %s\n", error.what());
    }
}
