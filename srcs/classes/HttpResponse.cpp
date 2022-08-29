#include "HttpResponse.hpp"
using std::map;
using std::pair;
using std::vector;
using std::string;
using std::cerr;
using std::endl;
using std::setw;
using std::left;

HttpResponse::HttpResponse(void)
: status_code(200), content_type("text/plain"), body(), http_version("HTTP/1.1")
{}

void HttpResponse::display(bool print_body) const {
	PRINTCOLOR(GREEN, "< HttpResponse >");
	cerr << left << setw(20) << "status_code: " << status_code << endl;
	cerr << left << setw(20) << "content_type: " << content_type << endl;
	cerr << left << setw(20) << "http_version: " << http_version << endl;
	if (print_body)
		cerr << left << setw(20) << "body: " << body << endl;
	cerr << endl;
}
