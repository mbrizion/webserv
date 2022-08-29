#include "webserv.hpp"

void l_fill_allow_methods(ConfigFile *config_data, string location_block)
{
	size_t found = location_block.find("allow_methods");
	size_t tmp_found = 0;
	size_t start = 0;
	if (found == string::npos)
		return ;
	int i = found;
	for (; location_block[i] && (isalpha(location_block[i]) || location_block[i] == '_'); i++);
	for (; location_block[i] && isspace(location_block[i]); i++);
	string tmp = location_block.substr(i, get_newline_index(i, location_block) - i);
	while (tmp_found != string::npos)
	{
		tmp_found = tmp.find(' ', tmp_found);
		string methods = to_uppercase(tmp.substr(start, tmp_found - start));
		if (!is_valid_methods(methods))
			print_error("Invalid methods directive. (location)");
		if (tmp_found == string::npos)
		{
			serv[serv_idx].locations[loc_idx].allow_methods.push_back(methods);
			return ;
		}
		serv[serv_idx].locations[loc_idx].allow_methods.push_back(methods);
		tmp_found++;
		start = tmp_found;
	}
}

void l_fill_location(ConfigFile *config_data, string location_block)
{
	size_t found = location_block.find("location");
	int i = found;
	for (; location_block[i] && isalpha(location_block[i]); i++);
	for (; location_block[i] && isspace(location_block[i]); i++)
		if (location_block[i] == '\n')
			print_error("Invalid location directive. (location)");
	serv[serv_idx].locations[loc_idx].location = location_block.substr(i, get_newline_index(i, location_block) - i);
}

void l_fill_index(ConfigFile *config_data, string location_block)
{
	size_t found = location_block.find("\tindex ");
	if (found == string::npos)
	{
		serv[serv_idx].locations[loc_idx].index = DEFAULT_INDEX;
		return ;
	}
	int i = 0;
	found++;
	string raw_directive = location_block.substr(found, get_newline_index(found, location_block) - found);
	if (raw_directive[i] && raw_directive[i + 1])
	{
		for(; raw_directive[i] && isalpha(raw_directive[i]); i++);
		for(; raw_directive[i] && isspace(raw_directive[i]); i++);
		raw_directive = raw_directive.substr(i);

		for(; raw_directive[i]; i++);
		serv[serv_idx].locations[loc_idx].index = raw_directive.substr(0, i);
		found = location_block.find("\tindex ", found + 1);
	}
	else
		print_error("Invalid index directive.(location)");
}

void l_fill_autoindex(ConfigFile *config_data, string location_block)
{
	int i  = 0;
	size_t found = location_block.find("\tautoindex ");
	if (found == string::npos){
		serv[serv_idx].locations[loc_idx].autoindex = false;
		return ;
	}
	found++;
	string raw_directive = location_block.substr(found, get_newline_index(found, location_block) - found);
	for (; raw_directive[i] && isalpha(raw_directive[i]); i++);
	for (; raw_directive[i] && isspace(raw_directive[i]); i++);
	string directive = raw_directive.substr(i, raw_directive.length() - i);
	i = 0;
	if (directive[i] && directive[i + 1])
	{
		if (!directive.compare("on"))
			serv[serv_idx].locations[loc_idx].autoindex = true;
		else if (!directive.compare("off"))
			serv[serv_idx].locations[loc_idx].autoindex = false;
		else
			print_error("Invalid autoindex directive. (location)");
	}
	else
		print_error("Invalid autoindex directive. (location)");
}

void l_fill_redirection(ConfigFile *config_data, string location_block)
{
	size_t found = location_block.find("redirection");
	if (found == string::npos) {
		serv[serv_idx].locations[loc_idx].redirection = "";
		return ;
	}
	string raw_directive = location_block.substr(found, get_newline_index(found, location_block) - found);
	serv[serv_idx].locations[loc_idx].redirection = clean_directive(raw_directive);
}

void l_fill_root(ConfigFile *config_data, string location_block)
{
	size_t found = location_block.find("root");
	int i = 0;
	string directive;
	for (;found != string::npos;)
	{
		string raw_directive = location_block.substr(found, get_newline_index(found, location_block) - found);
		directive = clean_directive(raw_directive);
		if (directive[i] && directive[i + 1])
		{
			for(; directive[i] && isspace(directive[i]); i++);
			directive = directive.substr(i);
			for(; directive[i]; i++);
			serv[serv_idx].locations[loc_idx].root = directive.substr(0, i);
			found = location_block.find("root", found + 1);
		}
		else
			print_error("Invalid root directive. (location)");
		i = 0;
	}
}

void l_fill_upload_store(ConfigFile *config_data, string location_block)
{
	size_t found = location_block.find("upload_store");
	int i = 0;
	string directive;
	for (;found != string::npos;)
	{
		string raw_directive = location_block.substr(found, get_newline_index(found, location_block) - found);
		directive = clean_directive(raw_directive);
		if (directive[i] && directive[i + 1])
		{
			for(; directive[i] && isspace(directive[i]); i++);
			directive = directive.substr(i);
			for(; directive[i]; i++);
			serv[serv_idx].locations[loc_idx].upload_store = directive.substr(0, i);
			found = location_block.find("upload_store", found + 1);
		}
		else
			print_error("Invalid upload_store directive. (location)");
		i = 0;
	}
}
