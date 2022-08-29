#include <string>
using std::string;
#include <algorithm>

string tolower_string(const string &s) {
	string ret;
	ret.resize(s.size());
	std::transform(s.begin(), s.end(), ret.begin(), ::tolower);
	return (ret);
}
