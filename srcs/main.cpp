#include "webserv.hpp"
#include <csignal>

//declare and init globals
const map<string, string>  g_typemap = init_typemap();
const int                  g_epfd = create_epoll_instance();

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "Usage: ./webserv [configuration file]" << std::endl;
		return (1);
	}

	//avoid closing server because of closed connections
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
		perror("signal"); PRINTPOS
		fatal_error("Failed to setup signal handlers");
	}

	ConfigFile base_struct = parser(av[1], ac);

	vector<Server> servers;
	for (vector<ServerBlock>::iterator it = base_struct.servers.begin(), ite = base_struct.servers.end(); it != ite; ++it) {
		servers.push_back(Server(*it));
	}

	servers[0].display(); //TMP

	run_server(servers);
	return (0);
}
