#include "webserv.hpp"
#include <algorithm>

string generate_autoindex(const string &uri, const string &path, EventData &evdata) {
	DIR *dir = opendir(path.c_str()); //don't forget closedir()
	if (!dir) {
		return (build_error_response(500, evdata));
	}

	//store directory names and file names in vectors
	struct dirent *ent;
	vector<string> dirnames;
	vector<string> filenames;
	while ((ent = readdir(dir)) != NULL) {
		//don't link current directory
		if (!strncmp(ent->d_name, ".", 2))
			continue ;
		//append slash to dirname
		#ifdef _DIRENT_HAVE_D_TYPE
		if (ent->d_type == DT_DIR) {
			dirnames.push_back(ent->d_name);
			continue ;
		}
		filenames.push_back(ent->d_name);
		#endif
	}
	closedir(dir);

	//sort each vector
	std::sort(filenames.begin(), filenames.end());
	std::sort(dirnames.begin(), dirnames.end());

	//generate autoindex body
	std::stringstream ss;
	ss << "<!DOCTYPE html><html><head><title>Index of " << uri << "</title></head>\n<body><h1>Index of " << uri << "</h1><hr><pre>\n";
	for (vector<string>::const_iterator it = dirnames.begin(), ite = dirnames.end(); it!=ite; ++it) {
		ss << "<a href=\"" << *it << "/\">" << *it << "/</a>\n";
	}
	for (vector<string>::const_iterator it = filenames.begin(), ite = filenames.end(); it!=ite; ++it) {
		ss << "<a href=\"" << *it << "\">" << *it << "</a>\n";
	}
	ss << "</pre><hr></body></html>";

	//generate response
	HttpResponse response;
	response.status_code = 200;
	response.http_version = "HTTP/1.1";
	response.content_type = "text/html";
	response.body = ss.str();
	return (raw_response(response));
}
