#include "webserv.hpp"

//find largest common prefix to uri and route
size_t	find_match_len(string uri, string route) {
	size_t i = 0;
	size_t ret = 0;
	for (;uri[i] && uri[i] == route[i];++i) {
		if (uri[i] == '/')
			ret = i;
	}
	return (ret);
}

//returns false if no route found
bool	select_route(EventData &data) {
	if (data.server_ptr->routes.count(data.request.uri)) {
		//route is a full path
		data.route_ptr = &((data.server_ptr->routes.find(data.request.uri))->second);
		//ressource is stored on the location's full path
		data.request.ressource_location = data.route_ptr->root;
		return (true);
	}

	//find longest route possible
	size_t longest_len = 0;
	for (map<string, Route>::const_iterator it = data.server_ptr->routes.begin(), ite = data.server_ptr->routes.end();it!=ite;++it) {
		if (longest_len >= it->first.size())
			continue ; //skip bad candidates
		size_t found_len = find_match_len(data.request.uri, it->first);
		if (found_len > longest_len) { //new best candidate
			longest_len = found_len;
			data.route_ptr = &it->second;
		}
	}
	if (longest_len) {
		//found partial route
		//ressource is stored on the location's path + non-matching route end
		data.request.ressource_location = data.route_ptr->root + data.request.uri.substr(longest_len);
		return (true);
	}

	//can still use route "/"
	if (data.server_ptr->routes.count("/")) {
		data.route_ptr = &((data.server_ptr->routes.find("/")->second));
		data.request.ressource_location = data.route_ptr->root + data.request.uri.substr(1);
		return (true);
	}

	//else: could not find a matching route -> 404
	return (false);
}
