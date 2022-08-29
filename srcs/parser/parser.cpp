#include "webserv.hpp"

void (*functptr_server[])(ConfigFile *config_data, string raw_directive)
	= {fill_host, fill_port, fill_error_pages, fill_server_name, fill_max_body_size, NULL};
void (*functptr_location[])(ConfigFile *config_data, string location_block)
	= {l_fill_index, l_fill_location, l_fill_allow_methods, l_fill_redirection, l_fill_root, l_fill_autoindex, l_fill_upload_store, NULL};

void fill_location(ConfigFile *config_data)
{
	int i = 0;
	while (*functptr_location[i])
		(*functptr_location[i++])(config_data, config_data->servers[serv_idx].locations[loc_idx].location_block);
}

void get_location(ConfigFile *config_data)
{
	size_t found = config_data->servers[serv_idx].server_block.find("location");
	if (found == string::npos)
	{
		config_data->servers[serv_idx].location_block_count = 0;
		return ;
	}
	config_data->servers[serv_idx].location_block_count = 1;
	while (found != string::npos)
	{
		// Create new location block in struct
		config_data->servers[serv_idx].locations.push_back(LocationBlock());
		config_data->servers[serv_idx].locations[loc_idx].location_block =
		config_data->servers[serv_idx].server_block.substr(found, get_block_end(found, config_data->servers[serv_idx].server_block) - found + 1);
		found = config_data->servers[serv_idx].server_block.find("location", found + 1);
		fill_location(config_data);
		config_data->servers[serv_idx].location_block_count++;
	}
}

/*
** fill_server() : Identify directive and fill them with proper content
*/
void fill_server(ConfigFile *config_data)
{
	int i = 0;
	while (*functptr_server[i])
		(*functptr_server[i++])(config_data, config_data->servers[serv_idx].server_block);
}

/*
**	get_server_data(): Put server block in a string to help parsing.
*/
void get_server_data(ConfigFile *config_data)
{
	config_data->servers[serv_idx].location_block_count = 0;
	// Store the position of the end } of server block
	config_data->server_block_end = get_block_end(config_data->server_block_start, config_data->raw_config_file);
	config_data->servers[serv_idx].server_block
	= config_data->raw_config_file.substr(config_data->server_block_start, config_data->server_block_end
	- (config_data->server_block_start - 1));
	get_location(config_data);
	size_t found = config_data->servers[serv_idx].server_block.find("location");
	while (found != string::npos)
	{
		config_data->servers[serv_idx].server_block =
		config_data->servers[serv_idx].server_block.erase(found, get_block_end(found, config_data->servers[serv_idx].server_block) - found + 1);
		found = config_data->servers[serv_idx].server_block.find("location");
	}
	fill_server(config_data);
}

/*
**	get_config_blocks(): push a new server block into vector's servers struct
*/
void get_config_blocks(ConfigFile *config_data)
{
	config_data->server_block_count = 0;
	size_t index = -1;
	for (size_t i = 0; i < config_data->raw_config_file.length(); i++)
	{
		size_t found = config_data->raw_config_file.find("server\n", index + 1, 7);
		if (found != string::npos)
		{
			config_data->server_block_count++;
			config_data->server_block_start = found;
			// Create new server block in struct
			config_data->servers.push_back(ServerBlock());
			get_server_data(config_data);
			index = found;
		}
	}
}

void check_block(ConfigFile *config_data)
{
	int open = 0;
	for (size_t i = 0; i < config_data->raw_config_file.length(); i++)
	{
		if (config_data->raw_config_file[i] && config_data->raw_config_file[i] == '{')
			open++;
		if (config_data->raw_config_file[i] && config_data->raw_config_file[i] == '}')
			open--;
	}
	if (open != 0)
		print_error("Config file error");
}

ConfigFile parser(char *config_file_path, int ac)
{
	ConfigFile config_data;
	get_raw_config_file(&config_data, config_file_path, ac);
	check_block(&config_data);
	get_config_blocks(&config_data);

	if (config_data.servers.empty()) {
		print_error("No server block configured");
	}
	return (config_data);
}
