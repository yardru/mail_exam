// "handler" class source file
//
// Created by Yaroslav Drugov on 20.07.16
// as part of "server" project
//

#include "handler.h"

static const int buf_size = 1024;
using namespace std;

struct uri_t
{
    string scheme;
    string password;
    string host;
    int port;
    string path;
    vector<pair<string, string> > query;
    string fragment;

    uri_t(const string &uri)
    {
        unsigned long pos[] = {-1, -1, -1, -1, 0, uri.find("?"), uri.find("#")};
        unsigned long &pos_scheme   = pos[0];
        unsigned long &pos_password = pos[1];
        unsigned long &pos_host     = pos[2];
        unsigned long &pos_port     = pos[3];
        unsigned long &pos_path     = pos[4];
        unsigned long &pos_query    = pos[5];
        unsigned long &pos_fragment = pos[6];

        for (int i = 0; i < 7; i++)
        {
            pos[i]++;
            unsigned long lenght = uri.length();
            for (int j = i + 1; j < 7; j++)
                if (pos[j] < lenght)
                {
                    lenght = pos[j];
                    break;
                }
            lenght -= pos[i];
            switch (i)
            {
                case 4:
                    path.append(uri, pos[i], lenght);
                    break;
                case 5:
                    // TODO
                    break;
                case 6:
                    fragment.append(uri, pos[i], lenght);
                    break;
            }
        }
    }
};

static vector<string> parse_uri(const string &uri)
{
    vector<string> res;

    return res;
}

handler_t::handler_t(const char *method_name) : method(method_name) {}
handler_get_t::handler_get_t() : handler_t("GET") {}

STATUS_CODE handler_get_t::operator()(istream &request, ostream &response)
{
    STATUS_CODE status = STATUS_CODE_OK;
    string uri, http_ver, message_body;

    request >> uri >> http_ver;

    uri_t u(uri);
    FILE *f = fopen(u.path.c_str(), "r");
    if (f != nullptr)
    {
        char buf[buf_size + 1];
        size_t len = buf_size;
        while (len == buf_size)
        {
            len = fread(buf, 1, buf_size, f);
            message_body.append(buf, len);
        }
        fclose(f);
    }
    else
        status = STATUS_CODE_NOT_FOUND;

    // Starting line
    response << http_ver << ' ' << status << "\n";
    // Headers
    response << "Content-Type: text/html\n";
    response << "Content-Lenght: " << message_body.length() << "\n";
    response << "Connection: closed\n";
    response << "\n";
    // Message Body
    response << message_body;

    return STATUS_CODE_OK;
}
