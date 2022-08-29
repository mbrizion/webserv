#include "webserv.hpp"

void print_error(string error)
{
	cerr << "Parsing error: "<< error << endl;
	exit (1);
}

/*
**	get_newline_index() : Return newline (\n) index or end of line if there is no newline 
*/
int get_newline_index(int current_idx, string server_block)
{
	if ((size_t)current_idx != string::npos)
		for (; server_block[current_idx] && server_block[current_idx] != '\n'; current_idx++);
	return (current_idx);
}

/*
**	get_raw_config_file() : Store the given config file in a string,
**	also check if the file is valid/exists.
*/
void get_raw_config_file(ConfigFile *config_data, char *config_file_path, int ac)
{
	std::ifstream file(config_file_path);
	if (file.fail() && ac != 1)
		fatal_error("Invalid path or file does not exists");
	else if (ac == 1)
		cerr << "Using default config file." << endl;
	else
		cerr << "Using config file: " << config_file_path << endl;
	string buf;
	while (std::getline(file, buf)){
		config_data->raw_config_file += buf;	// get config file
		config_data->raw_config_file += "\n";
	}
}

/*
**	get_block_end() :
**
**	Find the last (closing) curly braces and return his index
**
**	Exemple :
**
**			server {
**				listen blabla;
**				location {
**
**				}
**		}
**		↑ return this index
**
*/
int get_block_end(int start, string block)
{
	int open = 0;
	int i = 0;
	for (; block[start + i]; i++)
	{
		if (block[start + i] == '{')
			open++;
		if (block[start + i] == '}'){
			open--;
			if (open == 0){
				return (start + i);
			}
		}
	}
	return (open);
}

/*
**	Remove directive name (like : "listen" "server_name" etc..)
**	to keep only information (like : port/address for listen)
*/
string	remove_directive_name(string directive)
{
	int i = 0;
	for (; directive[i] && (isalpha(directive[i]) || directive[i] == '_'); i++);
	for (; directive[i] && isspace(directive[i]); i++);
	string tmp = directive.substr(i);
	return (tmp);
}

string clean_directive(string raw_directive)
{
	int i = 0;
	for (; raw_directive[i] && (isalpha(raw_directive[i]) || raw_directive[i] == '_'); i++);
	for (; raw_directive[i] && isspace(raw_directive[i]); i++);
	return(raw_directive.substr(i, raw_directive.length()));
}

int get_last_location(string location_blocks)
{
	size_t last_index = 0;
	size_t found = location_blocks.find("location");
	if (found == string::npos)
		return (0);
	found++;
	while (found != string::npos)
	{
		last_index = found;
		found = location_blocks.find("location", found + 1);
	}
	return (last_index);
}

string to_uppercase(string s)
{
	string tmp;
	size_t i = 0;
	for (; i < s.length(); i++)
		tmp[i] = toupper(s[i]);
	tmp[i] = '\0';
	return (tmp.c_str());
}

bool is_valid_methods(string methods)
{
	if (!methods.compare("POST") || !methods.compare("DELETE") || !methods.compare("GET"))
		return true;
	return false;
}
