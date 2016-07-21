// "def.h" header file
//
// Created by Yaroslav Drugov on 20.07.16
// as part of "server" project
//

#ifndef _DEF_H_
#define _DEF_H_

#include <iostream>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;
typedef std::shared_ptr<ip::tcp::socket> psocket;

void daemonize(const char *log_file_path = nullptr, const char *new_current_path = "/");

#endif // _DEF_H_
