#ifndef WEBSERV_DEFINES_HPP
#define WEBSERV_DEFINES_HPP

//tweakable settings
#define MAX_EVENTS 4096
#define TIMEOUT -1 //-1 = no timeout
#define LISTEN_BACKLOG 300
#define RECV_BUFFER_SIZE 2048
#define SEND_BUFFER_SIZE 4096

//default config settings
#define CLIENT_MAX_BODY_SIZE_DEFAULT 2048
#define DEFAULT_INDEX "index.html"
#define DEFAULT_PORT 8080
#define DEFAULT_HOST "127.0.0.1"

//CGI
#define CGI_REVISION "CGI/1.1"
#define SERV_SOFTWARE "webserv"

//cosmetic defines
#define STATE_LISTEN 0
#define STATE_RECV 1
#define STATE_SEND 2

#endif
