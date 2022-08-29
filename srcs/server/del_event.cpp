#include "webserv.hpp"

void	del_event(const int evfd, map<int,EventData> &evdata) {
	//remove associated event from interest list
	if (epoll_ctl(g_epfd, EPOLL_CTL_DEL, evfd, NULL) < 0) {
		perror("epoll_ctl"); PRINTPOS
		cerr << "g_epfd=" << g_epfd << " evfd=" << evfd << endl;
	}

	//close socket fd
	if (close(evfd) < 0) {
		perror("close"); PRINTPOS
		cerr << "evfd=" << evfd << endl;
	}

	//delete event data
	evdata.erase(evfd);
}
