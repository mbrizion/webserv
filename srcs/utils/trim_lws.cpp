#include <string>

//https://datatracker.ietf.org/doc/html/rfc822#section-3.3
//defines leading white spaces as SPACE / HTAB

//left trim
void trim_lws(std::string &str)
{
	str.erase(0, str.find_first_not_of(" \t"));
}

//right trim
void trim_rws(std::string &str)
{
	str.erase(str.find_last_not_of(" \t") + 1);
}

//both
void trim_lrws(std::string &str)
{
	trim_rws(str);
	trim_lws(str);
}
