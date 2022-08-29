NAME = webserv

LINK_PATH = /tmp/webserv
DEFAULT_CONF = ./conf_files/website.conf

CXX = c++
CXXFLAGS = -I incs/ -I srcs/classes -std=c++98 -Wall -Werror -Wextra -MMD -MP -g3

SRCS_FILES = classes/Cgi.cpp classes/EventData.cpp classes/HttpRequest.cpp classes/HttpResponse.cpp classes/Route.cpp classes/Server.cpp main.cpp parser/fill_location_directives.cpp parser/fill_server_directives.cpp parser/parser.cpp parser/parser_utils.cpp server/build_error_response.cpp server/build_http_response.cpp server/del_event.cpp server/expand_status_code.cpp server/fatal_error.cpp server/file_upload.cpp server/find_content_type.cpp server/generate_autoindex.cpp server/get_header.cpp server/init_listen_socket.cpp server/raw_response.cpp server/read_file.cpp server/redirect_response.cpp server/run_server.cpp server/select_route.cpp server/select_server.cpp server/switch_to_send_on_error.cpp setup/create_epoll_instance.cpp setup/init_typemap.cpp utils/ft_strnstr.cpp utils/get_line.cpp utils/iequals.cpp utils/isCgiOn.cpp utils/itostring.cpp utils/tolower_string.cpp utils/trim_lws.cpp
SRCS = $(addprefix srcs/, $(SRCS_FILES))
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(SRCS:%.cpp=%.d)

VALGRIND = valgrind -s --leak-check=full
RM = rm -f

###compilation rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) -j $(NAME)

###execution rules
run: $(NAME)
	./$(NAME) $(DEFAULT_CONF)

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) $(DEFAULT_CONF)

###testing rules

#URI:
u = test.html
#port:
p = 8080
#host:
h = localhost
curl:
	curl -v $(h):$(p)/$(u)
diff: SHELL:=/bin/bash
diff:
	diff -s <(curl -s $(h):$(p)/$(u)) <(cat $(u))

#file to upload:
f = ./website/assets/mini.txt
upload:
	curl -X POST --data-binary "@./website/assets/mini.txt" localhost:8080/upload
#curl -X POST -F 'file=@$(f)' $(h):$(p)/upload

delete:
	@echo "to delete" > ./website/uploads/to_delete
	curl -v -X DELETE $(h):$(p)/uploads/to_delete
	@echo "checking if file is still there:"
	@(test -f ./website/uploads/to_delete && echo "file was NOT deleted") || echo "file was deleted"

#send 10 and 11 bytes bodies to the second server, configured to accept max 10 bytes of bodylength
body:
	curl -v -X POST -H "Content-Type: plain/text" --data "0123456789" $(h):8081
	@echo
	curl -v -X POST -H "Content-Type: plain/text" --data "0123456789x" $(h):8081

print:
	$(info SRCS_FILES="$(SRCS_FILES)")
	$(info SRCS="$(SRCS)")
	$(info OBJS="$(OBJS)")
	$(info DEPS="$(DEPS)")

###special rules
.PHONY: all clean fclean re run valgrind curl diff upload delete body print
-include $(DEPS)
