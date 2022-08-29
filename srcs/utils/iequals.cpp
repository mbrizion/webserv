#include <string>
using std::string;
#include <cctype>

//compare strings, ignoring case
bool iequals(const string& a, const string& b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return (false);
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return (false);
	return (true);
}
