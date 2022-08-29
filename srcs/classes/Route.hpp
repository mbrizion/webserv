#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "color_printing.hpp"
#include "parser.hpp"

struct Route {
	Route(LocationBlock &location_block);


	//attributes
	bool get_is_allowed;
	bool post_is_allowed;
	bool delete_is_allowed;
	bool autoindex;
	std::string route;
	std::string redirection;
	std::string root;
	std::string index_file_name;
	std::string upload_store;


	//methods
	bool method_is_allowed(const std::string method) const;
	void display(void) const;


private:
	Route(void);
};

#endif
