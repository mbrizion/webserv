#include "webserv.hpp"

#include <sys/stat.h>
bool file_exists(const string& path) {
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

string	get_response(EventData& evdata) {
	string path = evdata.request.ressource_location;
	struct stat statbuf;
	if (stat(path.c_str(), &statbuf)) {
		if (errno == EACCES)
			return (build_error_response(403, evdata));
		if (errno == ELOOP||errno == ENAMETOOLONG||errno == ENOENT||errno == ENOTDIR)
			return (build_error_response(404, evdata));
		return (build_error_response(500, evdata));
	}

	/*
	** file requests
	*/
	if (statbuf.st_mode & S_IFREG) {
		if (isCgiOn(evdata.request.uri)) {
			Cgi cgi;
			cgi.execute(evdata.request);
			if (cgi.response_code >= 400)
				return (build_error_response(cgi.response_code, evdata));
			HttpResponse response;
			response.body = cgi.response_body;
			response.content_type = cgi.response_content_type;
			return (raw_response(response));
		}
		HttpResponse response;
		response.content_type = find_content_type(evdata.request.ressource_location);
		response.body = read_file(path);
		return (raw_response(response));
	}

	/*
	** directory requests
	*/
	if (statbuf.st_mode & S_IFDIR) {
		if (file_exists(path + evdata.route_ptr->index_file_name) == true) {
			//index file available -> send it
			HttpResponse response;
			response.content_type = find_content_type(path + evdata.route_ptr->index_file_name);
			response.body = read_file(path + evdata.route_ptr->index_file_name);
			return (raw_response(response));
		}
		//no index file -> try autoindex
		if (evdata.route_ptr->autoindex == true) {
			return (generate_autoindex(evdata.request.uri, path, evdata));
		}
		//no index file and no autoindex -> ERROR 403 Forbidden
		return (build_error_response(403, evdata));
	}

	//not a directory, not a file
	return (build_error_response(404, evdata));
}

string	delete_response(EventData& evdata) {
	HttpResponse response;
	if (remove(evdata.request.ressource_location.c_str()) == 0)
		response.status_code = 204;
	else {
		if (errno == EACCES)
			response.status_code = 403;
		else if (errno == ELOOP||errno == ENAMETOOLONG||errno == ENOENT||errno == ENOTDIR)
			response.status_code = 404;
		else
			response.status_code = 500;
	}
	return (raw_response(response));
}

#include <ctime>
string	build_http_response(EventData& evdata) {
	evdata.request.display(1);

	if (evdata.request.method == "GET")
		return (get_response(evdata));
	if (evdata.request.method == "POST") {
		if (isCgiOn(evdata.request.ressource_location) == false
		&& evdata.route_ptr->upload_store.size()) {
			//receive file uploads via binary-data
			std::time_t rawtime = std::time(NULL);
			const string filepath = evdata.route_ptr->upload_store + "upload_" + std::asctime(std::localtime(&rawtime));
			std::ofstream ofs(filepath.c_str());
			ofs << evdata.request.body.c_str();
			HttpResponse response;
			response.status_code = 204;
			return (raw_response(response));
		}
		return (get_response(evdata));
	}
	if (evdata.request.method == "DELETE")
		return (delete_response(evdata));
	return ("");
}
