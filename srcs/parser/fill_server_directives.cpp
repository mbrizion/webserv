#include "webserv.hpp"

void fill_error_pages(ConfigFile *config_data, string server_block)
{
	size_t found = server_block.find("error_pages ");
	if (found == string::npos)
	{
		map<int, string>::iterator it = serv[serv_idx].error_pages.end();
		serv[serv_idx].error_pages.insert(it, std::pair<int, string>(0, ""));
		return ;
	}
	int i = 0;
	int tmp = 0;
	string directive;
	int error_code;
	string error_page;
	for (;found != string::npos;)
	{
		string raw_directive = server_block.substr(found, get_newline_index(found, server_block) - found);
		directive = clean_directive(raw_directive);
		if (directive[i] && directive[i + 1])
		{
			i++;
			for(; directive[i] && !isspace(directive[i]); i++);
			error_code = atoi(directive.substr(0, i).c_str());
			for(; directive[i] && isspace(directive[i]); i++);
			tmp = i;
			for(; directive[i]; i++);
			error_page = directive.substr(tmp, i);
			map<int, string>::iterator it = serv[serv_idx].error_pages.end();
			if (error_code && !error_page.empty())
				serv[serv_idx].error_pages.insert(it, std::pair<int, string>(error_code, error_page));
			else
				if (found != string::npos)
					print_error("Invalid error_pages directive");
			found = server_block.find("error_pages ", found + 1);
		}
		else
			print_error("Invalid error_pages directive");
		i = 0;
	}
}

void fill_host(ConfigFile *config_data, string server_block)
{
	size_t found = server_block.find("host");
	if (found == string::npos)
	{
		serv[serv_idx].host = DEFAULT_HOST;
		return ;
	}
	string directive;
	string raw_directive = server_block.substr(found, get_newline_index(found, server_block) - found);
	directive = clean_directive(raw_directive);
	if (directive.size())
		serv[serv_idx].host = directive;
	else
		print_error("Invalid host directive");
}

void fill_server_name(ConfigFile *config_data, string server_block)
{
	size_t found = server_block.find("server_name");
	if (found == string::npos)
	{
		serv[serv_idx].server_name = "";
		return ;
	}
	int i = 0;
	string directive;
	for (;found != string::npos;)
	{
		string raw_directive = server_block.substr(found, get_newline_index(found, server_block) - found);
		directive = clean_directive(raw_directive);
		if (directive[i] && directive[i + 1])
		{
			for(; directive[i] && isspace(directive[i]); i++);
			directive = directive.substr(i);
			for(; directive[i]; i++);
			serv[serv_idx].server_name = directive.substr(0, i);
			found = server_block.find("server_name", found + 1);
		}
		else
			print_error("Invalid server_name directive");
		i = 0;
	}
}

bool is_numeric(const string& str)
{
	return (str.find_first_not_of("0123456789") == string::npos);
}

void fill_max_body_size(ConfigFile *config_data, string server_block)
{
	size_t found = server_block.find("client_max_body_size");
	if (found == string::npos)
	{
		serv[serv_idx].client_max_body_size = CLIENT_MAX_BODY_SIZE_DEFAULT;
		return ;
	}
	string directive;
	int value = 0;
	string raw_directive = server_block.substr(found, get_newline_index(found, server_block) - found);
	directive = clean_directive(raw_directive);
	if (directive.size() && is_numeric(directive)) //only accepts positive numbers
	{
		value = atoi(directive.c_str());
		serv[serv_idx].client_max_body_size = value;
	}
	else
		print_error("Invalid client_max_body_size directive");
}

void fill_port(ConfigFile *config_data, string server_block)
{
	size_t found = server_block.find("port");
	if (found == string::npos)
	{
		serv[serv_idx].port = DEFAULT_PORT;
		return ;
	}
	string directive;
	int value = 0;
	string raw_directive = server_block.substr(found, get_newline_index(found, server_block) - found);
	directive = clean_directive(raw_directive);
	if (directive.size() && is_numeric(directive)) //only accepts positive numbers
	{
		value = atoi(directive.c_str());
		serv[serv_idx].port = value;
	}
	else
		print_error("Invalid port directive");
}
