#include "webserv.hpp"

//status-line
//https://datatracker.ietf.org/doc/html/rfc2616#section-6.1
//general header fields
//https://datatracker.ietf.org/doc/html/rfc2616#section-4.5
//response header fields
//https://datatracker.ietf.org/doc/html/rfc2616#section-6.2
//entity header fields
//https://datatracker.ietf.org/doc/html/rfc2616#section-7.1
//response body
//https://datatracker.ietf.org/doc/html/rfc2616#section-7.2

string	raw_response(const HttpResponse &response) {
	std::stringstream raw_response;
	raw_response
		<< response.http_version
		<< " "
		<< expand_status_code(response.status_code)
		<< "\r\n"
		<< "Content-Type: "
		<< response.content_type
		<< "\r\n"
		<< "Content-Length: "
		<< itostring(response.body.size())
		<< "\r\n"
		<< "\n"
		<< response.body;

	return (raw_response.str());
}
