#include "Server.hpp"
using std::map;
using std::pair;
using std::vector;
using std::string;
using std::cerr;
using std::endl;
using std::setw;
using std::left;

Server::Server(ServerBlock &server_block) {
	PRINTCOLOR(BLUE, "Constructing Server");
	port = server_block.port;
	host = server_block.host;
	server_name = server_block.server_name;
	error_pages = server_block.error_pages;
	client_max_body_size = server_block.client_max_body_size;

	//fill Route map
	for (vector<LocationBlock>::iterator it = server_block.locations.begin(), ite = server_block.locations.end(); it != ite; ++it) {
		routes.insert(std::make_pair(it->location, Route(*it)));
	}
}

void Server::display() const {
	PRINTCOLOR(GREEN, "### server " + server_name);
	cerr << "running on " << host << ":" << port << endl;
	cerr << "max body size: " << client_max_body_size << endl;
	cerr << "custom error pages:" << endl;
	for (map<int,string>::const_iterator it = error_pages.begin(), ite = error_pages.end(); it!=ite; ++it) {
		cerr << it->first << ": " << it->second << endl;
	}
	for (map<string,Route>::const_iterator it = routes.begin(), ite = routes.end(); it!=ite; ++it) {
		it->second.display();
	}
	cerr << endl;
}
