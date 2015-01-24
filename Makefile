CFLAGS = -Wall -Werror -pedantic -ansi
all:bin
	g++ -o bin/rshell src/exec.cpp
rshell:bin
	g++ -o bin/rshell src/exec.cpp
bin:
	mkdir bin
