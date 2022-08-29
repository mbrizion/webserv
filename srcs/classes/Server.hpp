#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "color_printing.hpp"
#include "parser.hpp"
#include "Route.hpp"

struct Server {
	Server(ServerBlock &server_block);


	//attributes
	int                          port;
	unsigned long                client_max_body_size;
	std::string                  host;
	std::string                  server_name;
	std::map<int,std::string>    error_pages;
	std::map<std::string,Route>  routes; //key is the route path


	//methods
	void display(void) const;


private:
	Server(void);
};

#endif
