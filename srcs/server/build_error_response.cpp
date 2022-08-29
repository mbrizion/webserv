#include "webserv.hpp"
#include "webserv_default_error_pages.hpp"

const char *get_default_error_body(const int code) {
	switch (code) {
		case 400: return (DEFAULTPAGE_400);
		case 401: return (DEFAULTPAGE_401);
		case 402: return (DEFAULTPAGE_402);
		case 403: return (DEFAULTPAGE_403);
		case 404: return (DEFAULTPAGE_404);
		case 405: return (DEFAULTPAGE_405);
		case 406: return (DEFAULTPAGE_406);
		case 407: return (DEFAULTPAGE_407);
		case 408: return (DEFAULTPAGE_408);
		case 409: return (DEFAULTPAGE_409);
		case 410: return (DEFAULTPAGE_410);
		case 411: return (DEFAULTPAGE_411);
		case 412: return (DEFAULTPAGE_412);
		case 413: return (DEFAULTPAGE_413);
		case 414: return (DEFAULTPAGE_414);
		case 415: return (DEFAULTPAGE_415);
		case 416: return (DEFAULTPAGE_416);
		case 417: return (DEFAULTPAGE_417);
		case 418: return (DEFAULTPAGE_418);
		case 421: return (DEFAULTPAGE_421);
		case 422: return (DEFAULTPAGE_422);
		case 423: return (DEFAULTPAGE_423);
		case 424: return (DEFAULTPAGE_424);
		case 425: return (DEFAULTPAGE_425);
		case 426: return (DEFAULTPAGE_426);
		case 428: return (DEFAULTPAGE_428);
		case 429: return (DEFAULTPAGE_429);
		case 431: return (DEFAULTPAGE_431);
		case 451: return (DEFAULTPAGE_451);
		case 500: return (DEFAULTPAGE_500);
		case 501: return (DEFAULTPAGE_501);
		case 502: return (DEFAULTPAGE_502);
		case 503: return (DEFAULTPAGE_503);
		case 504: return (DEFAULTPAGE_504);
		case 505: return (DEFAULTPAGE_505);
		case 506: return (DEFAULTPAGE_506);
		case 507: return (DEFAULTPAGE_507);
		case 508: return (DEFAULTPAGE_508);
		case 510: return (DEFAULTPAGE_510);
		case 511: return (DEFAULTPAGE_511);
	}
	//should not happen
	return ("");
}

string build_error_response(const int code, EventData& evdata) {
	HttpResponse response;
	response.status_code = code;

	if (evdata.server_ptr && evdata.server_ptr->error_pages.count(code))
		response.body = read_file(evdata.server_ptr->error_pages.at(code));
	else
		response.body = get_default_error_body(code);

	std::stringstream raw_response;
	raw_response
		<< response.http_version
		<< " "
		<< expand_status_code(response.status_code)
		<< "\r\n"
		<< "Content-Length: "
		<< response.body.size()
		<< "\r\n\n"
		<< response.body;

	return (raw_response.str());
}
