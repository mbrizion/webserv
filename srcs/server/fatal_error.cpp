#include "webserv.hpp"

void	fatal_error(const string &msg)
{
	cerr << "\e[0;31m" << "Fatal error: " << msg << "\e[0m" << endl;
	exit(EXIT_FAILURE);
}
