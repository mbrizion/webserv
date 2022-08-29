#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "color_printing.hpp"

struct HttpResponse {
	HttpResponse(void);


	//attributes
	int status_code;
	std::string content_type;
	std::string body;
	std::string http_version;


	//methods
	void display(bool print_body = 1) const;
};

#endif
