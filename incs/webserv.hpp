#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "webserv_includes.hpp"
#include "webserv_defines.hpp"

//classes
#include "parser.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Server.hpp"
#include "Route.hpp"

#include "webserv_prototypes.hpp"
#include "color_printing.hpp"
#include "Cgi.hpp"

//declare globals
extern const std::map<std::string, std::string> g_typemap;
extern const int                                g_epfd;

#endif
