#include "Route.hpp"
using std::map;
using std::pair;
using std::vector;
using std::string;
using std::cerr;
using std::endl;
using std::setw;
using std::left;

Route::Route(LocationBlock &location_block) {
	PRINTCOLOR(BLUE, "Constructing route "+location_block.location)
	route = location_block.location;
	redirection = location_block.redirection;
	cerr<<"x"<<location_block.redirection<<endl;
	root = location_block.root;
	autoindex = location_block.autoindex;
	index_file_name = location_block.index;
	upload_store = location_block.upload_store;
	get_is_allowed = 0;
	post_is_allowed = 0;
	delete_is_allowed = 0;

	//set booleans for each supported method
	for (vector<string>::iterator it = location_block.allow_methods.begin(), ite = location_block.allow_methods.end(); it!=ite; ++it) {
		if (it->compare("GET") == 0) {get_is_allowed = 1;}
		else if (it->compare("POST") == 0) {post_is_allowed = 1;}
		else if (it->compare("DELETE") == 0) {delete_is_allowed = 1;}
	}
	if (!get_is_allowed && !post_is_allowed && !delete_is_allowed)
		PRINTCOLOR(MAGENTA, "Warning: no methods allowed for this route");
}

bool Route::method_is_allowed(const string method) const {
	if (method == "GET") {return (get_is_allowed);}
	if (method == "POST") {return (post_is_allowed);}
	if (method == "DELETE") {return (delete_is_allowed);}
	return (false);
}

void Route::display() const {
	PRINTCOLOR(GREEN, "*** route " + route);
	cerr << left << setw(20) << "route: " << route << endl;
	cerr << left << setw(20) << "root: " << root << endl;
	cerr << left << setw(20) << "redirection: " << redirection << endl;
	cerr << left << setw(20) << "index_file_name: " << index_file_name << endl;
	cerr << left << setw(20) << "autoindex: " << autoindex << endl;
	cerr << left << setw(20) << "upload_store: " << upload_store << endl;
	cerr << left << setw(20) << "allowed methods: "
		<< (get_is_allowed ? "GET " : "")
		<< (post_is_allowed ? "POST " : "")
		<< (delete_is_allowed ? "DELETE" : "")
		<< endl;
}
