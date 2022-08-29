#include "webserv.hpp"

int file_upload(HttpRequest request) { // the upload will block
	cerr << request.body << endl; // now we have 1st body

	/*std::istringstream stream(HttpRequest);
	string line;
	while (getline(stream, line) && line != "\r") {

	}*/
	return 0;
}
