#include "webserv.hpp"

//returns false if header is not present
//stores it in value
bool get_header(const map<string, string> &headers, const string &key, string &value) {
	if (headers.count(tolower_string(key)) == 0) {
		return (false);
	}
	value = headers.at(tolower_string(key));
	return (true);
}
