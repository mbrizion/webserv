#include "webserv.hpp"

//create an epoll instance
int create_epoll_instance(void) {
	PRINTCOLOR(BLUE, "Initializing epoll.")
	int epfd = epoll_create(1);
	if (epfd < 0) {
		perror("epoll_create"); PRINTPOS
		fatal_error("Failed to create an epoll instance");
	}
	return (epfd);
}
