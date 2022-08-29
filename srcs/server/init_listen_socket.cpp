#include "webserv.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int	init_listen_socket(int port) {
	PRINTCOLOR(BLUE, "Setting up a socket to listen on port "+itostring(port))
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket"); PRINTPOS
		fatal_error("Failed to create listening socket");
	}
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0) {
		perror("fcntl"); PRINTPOS
		close(sockfd);
		fatal_error("Failed to set listening socket as non blocking");
	}

	//avoid waiting for TIME_WAIT sockets after restarting server
	const int enable = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(int)) < 0) {
		perror("setsockopt"); PRINTPOS
		close(sockfd);
		fatal_error("Failed to set options of listening socket");
	}

	struct sockaddr_in socket_address;
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(port);

	//to bind to any interface:
	socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
	//to bind to one address:
	//socket_address.sin_addr.s_addr = inet_addr(host.c_str());

	if (bind(sockfd, (struct sockaddr*)&socket_address, sizeof(socket_address)) < 0) {
		perror("bind"); PRINTPOS
		fatal_error("Bind failed while setting up listening socket"); //TMP?
	}
	if (listen(sockfd, LISTEN_BACKLOG) < 0) {
		perror("listen"); PRINTPOS
		fatal_error("Listen failed while setting up listening socket");
	}
	return sockfd;
}
