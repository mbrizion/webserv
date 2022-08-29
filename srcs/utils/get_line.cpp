#include <string>
using std::string;

//get next line from request and delete it from the buffer, or eturn false
bool get_line(string &line, string &buff) {
	size_t end	= buff.find("\r\n");
	if (end != string::npos) {
		line = buff.substr(0, end);
		buff.erase(0, end + 2);
		return (true);
	}
	return (false);
}
