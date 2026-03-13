all: parser tests

parser:
	g++ -std=c++11 -Wall main.cpp lexer.cpp symbole.cpp automate.cpp state.cpp -o parser

tests:
	g++ -std=c++11 -Wall Tests.cpp lexer.cpp symbole.cpp automate.cpp state.cpp -o tests

clean:
	rm -f parser tests *.o