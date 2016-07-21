// "def.cpp" source file
//
// Created by Yaroslav Drugov on 20.07.16
// as part of "server" project
//

#include "def.h"

void daemonize(const char *log_file_path, const char *new_current_path)
{
    int pid = fork();

    if (pid)
    {
        std::cout << "waiting for daemonize\n";
        raise(SIGSTOP);
        std::cout << "successfully daemonize. new pid:" << pid << "\n";
        exit(0);
    }


    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    if (log_file_path)
        stderr = fopen(log_file_path, "w");

    chdir(new_current_path);
    setsid();
    kill(getppid(), SIGCONT);
}