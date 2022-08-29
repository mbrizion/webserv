#ifndef WEBSERV_DEFAULT_ERROR_PAGES_HPP
#define WEBSERV_DEFAULT_ERROR_PAGES_HPP

//hard-coded default error pages to avoid relying on files

#define DEFAULTPAGE_400 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>400 Bad Request</title></head><body><center><h1>400 Bad Request</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_401 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>401 Unauthorized</title></head><body><center><h1>401 Unauthorized</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_402 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>402 Payment Required</title></head><body><center><h1>402 Payment Required</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_403 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>403 Forbidden</title></head><body><center><h1>403 Forbidden</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_404 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>404 Not Found</title></head><body><center><h1>404 Not Found</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_405 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>405 Method Not Allowed</title></head><body><center><h1>405 Method Not Allowed</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_406 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>406 Not Acceptable</title></head><body><center><h1>406 Not Acceptable</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_407 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>407 Proxy Authentication Required</title></head><body><center><h1>407 Proxy Authentication Required</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_408 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>408 Request Timeout</title></head><body><center><h1>408 Request Timeout</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_409 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>409 Conflict</title></head><body><center><h1>409 Conflict</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_410 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>410 Gone</title></head><body><center><h1>410 Gone</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_411 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>411 Length Required</title></head><body><center><h1>411 Length Required</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_412 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>412 Precondition Failed</title></head><body><center><h1>412 Precondition Failed</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_413 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>413 Payload Too Large</title></head><body><center><h1>413 Payload Too Large</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_414 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>414 URI Too Long</title></head><body><center><h1>414 URI Too Long</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_415 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>415 Unsupported Media Type</title></head><body><center><h1>415 Unsupported Media Type</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_416 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>416 Range Not Satisfiable</title></head><body><center><h1>416 Range Not Satisfiable</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_417 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>417 Expectation Failed</title></head><body><center><h1>417 Expectation Failed</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_418 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>418 I\'m a teapot</title></head><body><center><h1>418 I\'m a teapot</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_421 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>421 Misdirected Request</title></head><body><center><h1>421 Misdirected Request</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_422 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>422 Unprocessable Entity</title></head><body><center><h1>422 Unprocessable Entity</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_423 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>423 Locked</title></head><body><center><h1>423 Locked</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_424 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>424 Failed Dependency</title></head><body><center><h1>424 Failed Dependency</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_425 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>425 Too Early</title></head><body><center><h1>425 Too Early</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_426 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>426 Upgrade Required</title></head><body><center><h1>426 Upgrade Required</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_428 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>428 Precondition Required</title></head><body><center><h1>428 Precondition Required</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_429 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>429 Too Many Requests</title></head><body><center><h1>429 Too Many Requests</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_431 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>431 Request Header Fields Too Large</title></head><body><center><h1>431 Request Header Fields Too Large</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_451 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>451 Unavailable For Legal Reasons</title></head><body><center><h1>451 Unavailable For Legal Reasons</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_500 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>500 Internal Server Error</title></head><body><center><h1>500 Internal Server Error</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_501 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>501 Not Implemented</title></head><body><center><h1>501 Not Implemented</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_502 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>502 Bad Gateway</title></head><body><center><h1>502 Bad Gateway</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_503 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>503 Service Unavailable</title></head><body><center><h1>503 Service Unavailable</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_504 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>504 Gateway Timeout</title></head><body><center><h1>504 Gateway Timeout</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_505 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>505 HTTP Version Not Supported</title></head><body><center><h1>505 HTTP Version Not Supported</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_506 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>506 Variant Also Negotiates</title></head><body><center><h1>506 Variant Also Negotiates</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_507 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>507 Insufficient Storage</title></head><body><center><h1>507 Insufficient Storage</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_508 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>508 Loop Detected</title></head><body><center><h1>508 Loop Detected</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_510 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>510 Not Extended</title></head><body><center><h1>510 Not Extended</h1></center><hr><center>webserv</center></body></html>"
#define DEFAULTPAGE_511 "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>511 Network Authentication Required</title></head><body><center><h1>511 Network Authentication Required</h1></center><hr><center>webserv</center></body></html>"

#endif