all: run

build:
	docker build -t test-nginx .

run: build
	docker run --name test-nginx -d -p 8090:8090 -p 8091:8091 -p 8092:8092 -p 8093:8093 -p 8094:8094 test-nginx
	docker logs -f test-nginx

stop:
	-docker stop test-nginx

rm: stop
	-docker rm test-nginx

re: rm run

logs:
	docker logs -f test-nginx

.PHONY: all build run stop rm re logs
