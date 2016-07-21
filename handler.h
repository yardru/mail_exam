// "handler" class header file
//
// Created by Yaroslav Drugov on 20.07.16
// as part of "server" project
//

#ifndef _HANDLER_H_
#define _HANDLER_H_

#include "def.h"

enum STATUS_CODE
{
    STATUS_CODE_OK = 200,
    STATUS_CODE_NOT_FOUND = 404,
};

class handler_t
{
public:
    std::string method;
    handler_t(const char *method_name);
    virtual STATUS_CODE operator()(std::istream &request, std::ostream &response) = 0;
};

class handler_get_t : public handler_t
{
public:
    handler_get_t();
    STATUS_CODE operator()(std::istream &request, std::ostream &response);
};


#endif // _HANDLER_H_
