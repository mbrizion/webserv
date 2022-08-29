#include "webserv.hpp"

void	run_server(const vector<Server> &servers) {
	/*
	**   Setting up the multiplexing
	*/
	map<int, EventData> evdata;
	struct epoll_event events[MAX_EVENTS];

	/*
	**   Setting up the server's listening sockets
	*/
	struct epoll_event ev;
	bzero(&ev, sizeof(ev));
	for (vector<Server>::const_iterator it = servers.begin(), ite = servers.end(); it!=ite; ++it) {
		int listen_sockfd = init_listen_socket(it->port);
		ev.events = EPOLLIN;
		ev.data.fd = listen_sockfd;
		evdata[listen_sockfd].fd = listen_sockfd;
		evdata[listen_sockfd].state = STATE_LISTEN;
		if (epoll_ctl(g_epfd, EPOLL_CTL_ADD, listen_sockfd, &ev) < 0) {
			perror("epoll_ctl"); PRINTPOS
			fatal_error("Failed to add epoll event for listening socket");
		}
	}

	/*
	**   Starting the server
	*/
	while (1) { //main server loop: wait for events
		int ready_fds = epoll_wait(g_epfd, events, MAX_EVENTS, TIMEOUT);
		if (ready_fds < 0) {
			perror("epoll_wait"); PRINTPOS
			continue ;
		}
		if (ready_fds == 0) {
			PRINTCOLOR(GREEN, "Epoll timeout")
			continue ;
		}

		for (int i = 0; i < ready_fds; ++i) { //secondary loop: handle events one by one
			//fd of the event we are currently handling
			int evfd = events[i].data.fd;

			/*
			**      EVENT ERRORS
			**
			** handling of errors and hangups
			*/
			if (events[i].events & EPOLLERR) {
				perror("EPOLLERR"); PRINTPOS
				PRINTCOLOR(RED, "EPOLLERR | event="+itostring(i)+" fd="+itostring(evfd))
				del_event(evfd, evdata);
				continue ;
			}
			if (events[i].events & EPOLLHUP) {
				PRINTCOLOR(RED, "EPOLLHUP: connection closed by peer | event="+itostring(i)+" fd="+itostring(evfd))
				del_event(evfd, evdata);
				continue ;
			}

			/*
			**      LISTEN EVENT
			**
			** handling of connection requests
			*/
			if (evdata[evfd].state == STATE_LISTEN) {
				PRINTCOLOR(YELLOW, "<> listening socket | event="+itostring(i)+" fd="+itostring(evdata[evfd].fd))

				//get a fd for our recv/send socket
				int conn_sockfd = accept(evdata[evfd].fd, NULL, NULL);
				if (conn_sockfd < 0) {
					perror("accept"); PRINTPOS
					continue ;
				}
				//PRINTCOLOR(GREEN, "Client connected | event="+itostring(i)+" fd="+itostring(conn_sockfd));
				if (fcntl(conn_sockfd, F_SETFL, O_NONBLOCK) < 0) {
					perror("fcntl"); PRINTPOS
					continue ;
				}

				//init event data for reading
				evdata[conn_sockfd].fd = conn_sockfd;
				evdata[conn_sockfd].state = STATE_RECV;

				//create new event and add it to the interest list
				ev.events = EPOLLIN|EPOLLOUT;
				ev.data.fd = conn_sockfd;
				if (epoll_ctl(g_epfd, EPOLL_CTL_ADD, conn_sockfd, &ev) < 0) {
					perror("epoll_ctl"); PRINTPOS
					continue ;
				}
			}

			/*
			**      RECV EVENT
			**
			** handling of HTTP requests
			*/
			else if (evdata[evfd].state == STATE_RECV) {
				PRINTCOLOR(YELLOW, "<> readable socket | event="+itostring(i)+" fd="+itostring(evfd))
				vector<char> recv_buffer(RECV_BUFFER_SIZE+1);
				int bytes_received = recv(evfd, &recv_buffer[0], RECV_BUFFER_SIZE, 0);
				if (bytes_received < 0) {
					//either the call would block or there was an error
					//if (errno != EAGAIN && errno != EWOULDBLOCK) {perror("recv"); PRINTPOS} //TMP
					continue ;
				}
				if (bytes_received == 0) {
					//stream socket peer has performed an orderly shutdown
					PRINTCOLOR(GREEN, "Cleanup (connect closed in recv state) | event="+itostring(i)+" fd="+itostring(evfd))
					del_event(evfd, evdata);
					continue ;
				}
				evdata[evfd].request_buff.append(recv_buffer.begin(), recv_buffer.end());

				/*
				** Parsing of: Request-Line
				** Method SP Request-URI SP HTTP-Version CRLF
				** https://datatracker.ietf.org/doc/html/rfc2616#section-5.1
				*/
				if (evdata[evfd].parsed_reqline == false) {
					string line;
					if (get_line(line, evdata[evfd].request_buff) == false)
						continue ;
					std::istringstream stream(line);
					getline(stream, line, ' ');
					if (line != "GET" && line != "POST" && line != "DELETE") {
						//method not implemented -> ERROR 501
						switch_to_send_on_error(501, evdata[evfd]);
						continue ;
					}
					evdata[evfd].request.method = line;
					getline(stream, line, ' ');

					//extract php query string
					size_t pos = line.find_first_of("?");
					if (pos != line.npos) {
						evdata[evfd].request.query_string = line.substr(pos+1);
						line = line.substr(0, pos);
					}

					evdata[evfd].request.uri = line;
					getline(stream, line, '\n');
					evdata[evfd].request.http_version = line;

					evdata[evfd].parsed_reqline = true;
				}

				/*
				** Parsing of: Request Header Fields
				** https://datatracker.ietf.org/doc/html/rfc2616#section-4.2
				** https://datatracker.ietf.org/doc/html/rfc822#section-3.1.2
				*/
				if (evdata[evfd].parsed_headers == false) {
					string line;
					while (get_line(line, evdata[evfd].request_buff) == true && line != "") {
						std::size_t pos = line.find(": ");
						if (pos == line.npos) {
							switch_to_send_on_error(400, evdata[evfd]);
							continue ;
						}
						string header_name = tolower_string(line.substr(0, pos));
						trim_lrws(header_name);
						string header_value = line.substr(pos+1);
						trim_lrws(header_value);
						evdata[evfd].request.headers[header_name] = header_value;
					}

					if (line != "") {
						//we need to finish parsing headers -> wait for next event to refill buffer
						continue ;
					}

					/*
					** Headers should have all been received:
					** Parse all we need from headers now
					*/
					evdata[evfd].parsed_headers = true;

					//A valid request needs a host header
					string host_value;
					if (get_header(evdata[evfd].request.headers, "host", host_value) == false) {
						//no host header -> ERROR 400 Bad Request
						switch_to_send_on_error(400, evdata[evfd]);
						continue ;
					}
					//We select the appropriate server (from host header)
					if (select_server(servers, host_value, evdata[evfd]) == false) {
						//no server can handle this request -> ERROR 400 Bad Request
						switch_to_send_on_error(400, evdata[evfd]);
						continue ;
					}

					//We select the route and get the ressource's location path
					if (select_route(evdata[evfd]) == false) {
						//no route -> ERROR 404
						switch_to_send_on_error(404, evdata[evfd]);
						continue ;
					}

					//We check that this route accepts the request's method
					if (evdata[evfd].route_ptr->method_is_allowed(evdata[evfd].request.method) == false) {
						//method not allowed -> ERROR 405
						switch_to_send_on_error(405, evdata[evfd]);
						continue ;
					}

					//Check if there is a redirection
					if (evdata[evfd].route_ptr->redirection.size()) {
						evdata[evfd].state = STATE_SEND;
						evdata[evfd].response_buff = redirect_response(evdata[evfd]);
						continue ;
					}

					//We check if the request is multipart and store its boundary if yes
					string content_type_value;
					if ((get_header(evdata[evfd].request.headers, "content-type", content_type_value) == true)
					&& (content_type_value.find("multipart/form-data") != string::npos)) {
						evdata[evfd].request.is_multipart = true;
						string to_find = "boundary=";
						std::size_t pos = content_type_value.find(to_find) + to_find.size();
						if (pos == string::npos) {
							//multipart with no boundary -> ERROR 400 Bad Request
							switch_to_send_on_error(400, evdata[evfd]);
							continue ;
						}
						while ( content_type_value[pos] == '-' )
							pos++;
						evdata[evfd].request.boundary = content_type_value.substr(pos);
					}
				}

				/*
				** Parsing of: Message body
				** https://datatracker.ietf.org/doc/html/rfc2616#section-4.3
				*/
				if (strlen(evdata[evfd].request_buff.c_str()) > evdata[evfd].server_ptr->client_max_body_size) {
					//client body size is outside limits -> ERROR 413
					switch_to_send_on_error(413, evdata[evfd]);
					continue ;
				}

				if (ft_strnstr(&recv_buffer[0], "\r\n\r\n", bytes_received) == NULL && evdata[evfd].request.is_multipart==false) {
					//we need to finish receiving body -> wait for next event to refill buffer
					continue ;
				}

				//we received the full body

				if (evdata[evfd].request.is_multipart == true) {
					//PRINTCOLOR(YELLOW, "Multipart: new body:");

					if (evdata[evfd].request.body.size() && evdata[evfd].request.body.end()[-1] == '\0')
						evdata[evfd].request.body.erase(evdata[evfd].request.body.end()-1);
					evdata[evfd].request.body.append(evdata[evfd].request_buff);
					evdata[evfd].request_buff.erase();

					//check if it's the last part (boundary + "--")
					if (evdata[evfd].request.body.find(evdata[evfd].request.boundary + "--") == string::npos) {
						//it's not the last part -> refresh buffer
						//PRINTCOLOR(YELLOW, "Multipart: not the last part of request");
						continue ;
					}
					//PRINTCOLOR(YELLOW, "Multipart: last part of request");
					//it's the last part -> send
				}
				else {
					evdata[evfd].request.body = evdata[evfd].request_buff;
					evdata[evfd].request_buff.erase();
					//not multipart -> send
				}

				//it's time to send -> build the response
				evdata[evfd].response_buff = build_http_response(evdata[evfd]);
				evdata[evfd].state = STATE_SEND;
				continue ;
			}

			/*
			**      SEND EVENT
			**
			** handling of HTTP responses
			*/
			else if (evdata[evfd].state == STATE_SEND) {
				PRINTCOLOR(YELLOW, "<> writeable socket | event="+itostring(i)+" fd="+itostring(evfd))
				string to_send = evdata[evfd].response_buff.substr(0, SEND_BUFFER_SIZE);
				ssize_t bytes_sent = send(evfd, to_send.c_str(), to_send.size(), 0);
				if (bytes_sent < 0) {
					//perror("send"); PRINTPOS //TMP
					//either the call would block or there was an error
					continue ;
				}
				if (bytes_sent == 0) {
					//stream socket peer has performed an orderly shutdown
					PRINTCOLOR(GREEN, "Cleanup (connect closed in send state) | event="+itostring(i)+" fd="+itostring(evfd))
					del_event(evfd, evdata);
					continue ;
				}

				evdata[evfd].response_buff.erase(0, bytes_sent);
				//send complete
				if (evdata[evfd].response_buff.size() == 0) {
					//cerr << "Sent HTTP response:\n" << to_send << endl;
					PRINTCOLOR(GREEN, "Cleanup (sent response) | event="+itostring(i)+" fd="+itostring(evfd))
					del_event(evfd, evdata);
					continue ;
				}
			}
			else { //should not happen
				PRINTCOLOR(RED, "/!\\ something weird happened | event="+itostring(i)+" fd="+itostring(evfd))
				del_event(evfd, evdata);
				continue ;
			}
		} //secondary loop
	} //main loop
}
