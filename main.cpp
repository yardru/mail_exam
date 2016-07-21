#include "server.h"

int main(int argc, char **argv)
{
    daemonize();

    server_t server(argc, argv);

    server << new handler_get_t;

    server.run();

    return 0;
}