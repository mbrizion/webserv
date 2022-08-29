#include "EventData.hpp"
using std::map;
using std::pair;
using std::vector;
using std::string;
using std::cerr;
using std::endl;
using std::setw;
using std::left;

void EventData::display(void) const {
	PRINTCOLOR(GREEN, "< EventData >");
	cerr << left << setw(20) << "parsed_headers: " << parsed_headers << endl;
	cerr << left << setw(20) << "parsed_reqline: " << parsed_reqline << endl;
	cerr << left << setw(20) << "fd: " << fd << endl;
	cerr << left << setw(20) << "state: " << state << endl;
	cerr << left << setw(20) << "bytes_sent: " << bytes_sent << endl;
	cerr << left << setw(20) << "request_buff: " << request_buff << endl;
	cerr << left << setw(20) << "response_buff: " << response_buff << endl;
	cerr << endl;
}
