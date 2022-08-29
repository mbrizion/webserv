#ifndef EVENTDATA_HPP
#define EVENTDATA_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "color_printing.hpp"
#include "HttpRequest.hpp"
#include "Route.hpp"
#include "Server.hpp"

struct EventData {


	//attributes
	bool           parsed_headers, parsed_reqline;
	int            fd, state, bytes_sent;
	std::string    request_buff, response_buff;
	HttpRequest    request;
	const Route*   route_ptr;
	const Server*  server_ptr;


	//methods
	void display(void) const;
};

#endif
