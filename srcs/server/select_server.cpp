#include "webserv.hpp"

//returns false if no server will handle the request
bool	select_server(const vector<Server> &servers, const string &host_value, EventData &data) {
	std::size_t pos = host_value.find(":");
	string host = host_value.substr(0, pos);

	int port = atoi(host_value.substr(pos+1).c_str());
	if (!host.size() || port<1) {
		return (false);
	}

	//check if host = server name
	for (vector<Server>::const_iterator it = servers.begin(), ite = servers.end();it!=ite;++it) {
		if (it->server_name == host && it->port == port) {
			data.server_ptr = &*it;
			return (true);
		}
	}

	//check if host = host
	for (vector<Server>::const_iterator it = servers.begin(), ite = servers.end();it!=ite;++it) {
		if (it->host == host && it->port == port) {
			data.server_ptr = &*it;
			return (true);
		}
	}

	//can't find a server to handle this request
	return (false);
}
