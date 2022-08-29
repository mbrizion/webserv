#include <string>
#include <sstream>

std::string itostring(int const nb)
{
	std::stringstream ss;
	ss << nb;
	return (ss.str());
}
