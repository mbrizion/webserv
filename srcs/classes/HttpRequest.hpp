#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

#include "color_printing.hpp"

struct HttpRequest {
	HttpRequest(void);


	//attributes
	bool is_multipart;
	std::string method;
	std::string uri;
	std::string query_string;
	std::string ressource_location;
	std::string boundary;
	std::string body;
	std::string http_version;
	std::map<std::string, std::string> headers;
	//key: header name stored in lowercase and without terminating semicolumn
	std::queue<std::string> multipart_data;


	//methods
	void display(bool print_body = 1) const;
	std::string merge_multipart(void);
};

#endif
