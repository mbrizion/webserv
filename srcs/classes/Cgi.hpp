#ifndef CGI_HPP
#define CGI_HPP

#include <cstring>

class Cgi {
public:
	Cgi();
	~Cgi();
	void execute(const HttpRequest &request);
	char** conv_env(const HttpRequest &request);
	string getCgiData(string requested_data);


//attributes of response
//length is handled by raw_response() directly
public:
	int response_code;
	string response_body;
	string response_content_type;

//attributes of request
private:
	std::map<string, string> _env;
	string _content_length;
	string _content_type;
	string _gateway_interface;
	string _path_info;
	string _path_translated;
	string _query_string;
	string _redirect_status;
	string _remote_addr;
	string _request_method;
	string _request_uri;
	string _script_name;
	string _server_name;
	string _server_port;
	string _server_protocol;
	string _server_software;
	string _auth_type;
};

#endif
