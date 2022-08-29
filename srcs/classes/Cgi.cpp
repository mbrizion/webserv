//Common gateway interface:
//https://www.rfc-editor.org/rfc/rfc3875

#include "webserv.hpp"
#include "Cgi.hpp"
#include <cstring>

string Cgi::getCgiData(string requested_data)
{
	if (_env.find(requested_data) != _env.end())
		return (_env.find(requested_data)->second);
	return (_env.find(requested_data)->second);
}

Cgi::Cgi() {
	response_code = 200;
}

Cgi::~Cgi(){}

char **Cgi::conv_env(const HttpRequest &request)
{
	_env["AUTH_TYPE"] = "";

	string valbuff;
	if (request.method == "POST") {
		//headers for post requests
		if (get_header(request.headers, "content-length", valbuff) == false) {
			valbuff = "0";
		}
		_env["CONTENT_LENGTH"] = valbuff;

		if (get_header(request.headers, "content-type", valbuff) == false)
			valbuff = "text/raw";
		_env["CONTENT_TYPE"] = valbuff;
	}

	_env["GATEWAY_INTERFACE"] = CGI_REVISION;
	_env["PATH_INFO"] = "";
	_env["REMOTE_ADDR"] = DEFAULT_HOST;
	_env["PATH_TRANSLATED"] = request.ressource_location;
	_env["QUERY_STRING"] = request.query_string;
	_env["REQUEST_URI"] = request.uri;
	_env["REQUEST_METHOD"] = request.method;
	_env["SCRIPT_NAME"] = request.ressource_location;
	_env["SERVER_NAME"] = "localhost";
	_env["SERVER_PORT"] = "8080";
	_env["SERVER_PROTOCOL"] = request.http_version;
	_env["SERVER_SOFTWARE"] = SERV_SOFTWARE;
	_env["REDIRECT_STATUS"] = "200";
	char **conv = new char *[_env.size() + 1];
	string tmp;
	int i = 0;
	for (std::map<string, string>::iterator it = _env.begin(); it != _env.end(); it++, i++)
	{
		tmp = it->first + "=" + it->second + '\0';
		conv[i] = new char[tmp.length() + 1];
		tmp.copy(conv[i], tmp.length());
	}
	conv[i] = NULL;
	return conv;
}

#include <sys/wait.h>
void Cgi::execute(const HttpRequest &request)
{
	int input_pipefd[2];
	pipe(input_pipefd);
	//input_pipefd[1] -> serv writes request body
	//input_pipefd[0] -> cgi reads request body

	int output_pipefd[2];
	pipe(output_pipefd);
	//output_pipefd[1] -> cgi writes output
	//output_pipefd[0] -> serv reads cgi output

	pid_t cgi_pid;
	if ((cgi_pid = fork()) == 0) {

		/*
		** child: CGI
		*/
		close(input_pipefd[1]);
		close(output_pipefd[0]);

		//read post body
		dup2(input_pipefd[0], STDIN_FILENO);
		close(input_pipefd[0]);

		//redirect the child's stdout to the pipe
		dup2(output_pipefd[1], STDOUT_FILENO);
		close(output_pipefd[1]);

		char **env = conv_env(request);
		char * const * nul = NULL;
		if (size_t found = request.ressource_location.find(".php") != string::npos)
			execve("/usr/bin/php-cgi7.4", nul, env);
		else if (size_t found = request.ressource_location.find(".cgi") != string::npos)
			execve(request.ressource_location.c_str(), nul, env);
		exit (1);
	}

	if (cgi_pid < 0) {
		response_code = 500;
		return ;
	}

	/*
	** parent: webserv
	*/
	close(input_pipefd[0]);
	close(output_pipefd[1]);

	//send body to child (for POST requests)
	int wret = write(input_pipefd[1], request.body.c_str(), request.body.size());
	(void)wret;
	close(input_pipefd[1]);

	//recover output from child
	char read_buffer[10001];
	// wait for child process to end
	waitpid(-1, NULL, 0);
	int rret = read(output_pipefd[0], read_buffer, 10000);
	read_buffer[rret] = '\0';
	string cgi_output(read_buffer);

	//get content_type
	string line;
	while (get_line(line, cgi_output) && line != "") {
		if (ssize_t pos = line.find("Content-type:") != string::npos) {
			pos = line.find_first_of(":", pos);
			pos = line.find_first_not_of(" ", pos+1);
			response_content_type = line.substr(pos);
			response_content_type = "text/plain";
		}
	}

	//get body
	response_body = cgi_output;
}
