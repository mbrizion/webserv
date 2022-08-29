#include "webserv.hpp"

string	redirect_response(const EventData &evdata) {
	std::stringstream raw_response;
	raw_response
		<< evdata.request.http_version
		<< " "
		<< 301
		<< "\r\n"
		<< "Location: "
		<< evdata.route_ptr->redirection
		<< "\r\n"
		<< "\n";
	return (raw_response.str());
}
