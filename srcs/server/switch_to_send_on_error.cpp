#include "webserv.hpp"

void	switch_to_send_on_error(const int code, EventData &evdata) {
	evdata.response_buff = build_error_response(code, evdata);
	evdata.state = STATE_SEND;
	evdata.request_buff.erase();
}
