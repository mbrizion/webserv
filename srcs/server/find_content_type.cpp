#include "webserv.hpp"

//MIME types RFC:
//https://www.rfc-editor.org/rfc/rfc2046
string find_content_type(const string &filepath) {
	std::size_t found = filepath.find_last_of(".");

	//no extension
	if (found == string::npos)
		return ("text/plain");

	map<string,string>::const_iterator it = g_typemap.find(filepath.substr(found));

	if (it == g_typemap.end()) {
		//unknown extension
		return ("text/plain");
	}

	//extension matches a known type
	return (it->second);
}
