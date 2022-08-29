#include "webserv.hpp"

string	read_file(const string& path) {
	std::ofstream file;
	file.open(path.c_str(), std::ifstream::in);
	if (file.is_open() == false)
		return ("");

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return (buffer.str());
}
