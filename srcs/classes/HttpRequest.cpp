#include "HttpRequest.hpp"
using std::map;
using std::pair;
using std::vector;
using std::string;
using std::cerr;
using std::endl;
using std::setw;
using std::left;

HttpRequest::HttpRequest(void)
: is_multipart(false), method(), uri(), ressource_location(), boundary(), body(), http_version(), headers()
{}

void HttpRequest::display(bool print_body) const {
	PRINTCOLOR(GREEN, "< HttpRequest >");
	cerr << left << setw(20) << "method: " << method << endl;
	cerr << left << setw(20) << "uri: " << uri << endl;
	cerr << left << setw(20) << "query_string: " << query_string << endl;
	cerr << left << setw(20) << "ressource_location: " << ressource_location << endl;
	cerr << left << setw(20) << "is_multipart: " << is_multipart << endl;
	cerr << left << setw(20) << "boundary: " << boundary << endl;
	cerr << left << setw(20) << "http_version: " << http_version << endl;
	if (print_body) {
		PRINTCOLOR(GREEN, "< HttpRequest body >");
		cerr << body << endl;
	}
	PRINTCOLOR(GREEN, "< HttpRequest headers >");
	for (map<string, string>::const_iterator it = headers.begin(), ite = headers.end(); it != ite; ++it)
		cerr << it->first << ": " << it->second << endl;
	cerr << endl;
}

string HttpRequest::merge_multipart(void) {
	if (!is_multipart) {
		PRINTCOLOR(MAGENTA, "Not multipart")
		return ("");
	}
	//TODO: piece together the files
	return ("");
}
