#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <map>

#define serv config_data->servers
#define serv_idx config_data->server_block_count - 1
#define loc_idx serv[serv_idx].location_block_count - 1

struct LocationBlock {
	bool                      autoindex;
	std::string               redirection;
	std::string               root;
	std::string               index;
	std::string               upload_store;
	std::vector<std::string>  allow_methods;
	//internals
	std::string location;
	std::string location_block;
};

struct ServerBlock {
	int                          port;
	int                          client_max_body_size;
	std::string                  host;
	std::string                  server_name;
	std::vector<LocationBlock>   locations;
	std::map<int, std::string>   error_pages;
	//internals
	int         location_block_count;
	std::string server_block;
};

struct ConfigFile {
	//internals
	int                        server_block_count;
	int                        server_block_start;
	int                        server_block_end;
	std::string                raw_config_file;
	std::vector<ServerBlock>   servers;
};

#endif