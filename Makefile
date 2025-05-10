all: run clean

run: 
	gcc -Werror -Wextra -Wall src/sockets.c -o sockets
	# strace -f ./sockets
	./sockets

clean: 
	rm -rf ./sockets
