
CPP_FLAGS := -std=c++11 -Wall -I src/include -I src -DDEBUG
CC := g++

socket: src/io/socket.cpp src/io/socket_test.cpp
	${CC} -o socket_test.out ${CPP_FLAGS} src/io/socket.cpp src/io/socket_test.cpp

clean:
	rm socket_test