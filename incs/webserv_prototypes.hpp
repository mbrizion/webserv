#ifndef WEBSERV_PROTOTYPES_HPP
#define WEBSERV_PROTOTYPES_HPP

struct Server;
struct Route;
struct HttpRequest;
struct HttpResponse;
struct EventData;
#include "Server.hpp"
#include "Route.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "EventData.hpp"

//server
string			build_error_response(const int code, EventData& evdata);
string			build_http_response(EventData& evdata);
void			del_event(const int evfd, map<int, EventData>& evdata);
string			expand_status_code(int code);
void			fatal_error(const string& msg);
string			find_content_type(const string& filepath);
string			generate_autoindex(const string& uri, const string& path, EventData& evdata);
bool			get_header(const map<string, string>& headers, const string& key, string& value);
int				init_listen_socket(const int port);
string			raw_response(const HttpResponse& response);
string			read_file(const string& path);
string			redirect_response(const EventData &evdata);
void			run_server(const vector<Server>& servers);
bool			select_route(EventData& data);
bool			select_server(const vector<Server>& servers, const string& host_value, EventData& data);
void			switch_to_send_on_error(const int code, EventData& data);

//setup
int							create_epoll_instance(void);
const map<string, string>	init_typemap(void);

//parser
string			clean_directive(string raw_directive);
int				get_block_end(int start, string block);
int				get_last_location(string location_blocks);
int				get_newline_index(int current_idx, string server_block);
void			get_raw_config_file(ConfigFile* config_data, char* config_file_path, int ac);
void			fill_error_pages(ConfigFile* config_data, string server_block);
void 			fill_host(ConfigFile* config_data, string server_block);
void			fill_max_body_size(ConfigFile* config_data, string server_block);
void 			fill_port(ConfigFile* config_data, string server_block);
void			fill_server_name(ConfigFile* config_data, string server_block);
bool 			is_valid_methods(string methods);
void			l_fill_allow_methods(ConfigFile* config_data, string location_block);
void			l_fill_autoindex(ConfigFile* config_data, string server_block);
void			l_fill_index(ConfigFile* config_data, string server_block);
void			l_fill_location(ConfigFile* config_data, string location_block);
void			l_fill_redirection(ConfigFile* config_data, string server_block);
void			l_fill_root(ConfigFile* config_data, string server_block);
void			l_fill_upload_store(ConfigFile *config_data, string location_block);
ConfigFile		parser(char* config_file_path, int ac);
void			print_error(string error);
string			to_uppercase(string s);

//utils
char			*ft_strnstr(const char* s1, const char* s2, const size_t len);
bool			get_line(string& line, string& buff);
bool			iequals(const string& a, const string& b);
string			itostring(const int nb);
string			tolower_string(const string& s);
void			trim_lrws(string& str);
bool			isCgiOn(string root);


#endif
