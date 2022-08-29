#include <string>
using std::string;

bool isCgiOn(string root)
{
	if (root.length() < 4)
		return (false);
	string tmp = root.substr(root.length() - 4);
	if (!tmp.compare(".php"))
		return (true);
	return (false);
}