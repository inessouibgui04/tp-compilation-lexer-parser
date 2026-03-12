# Makefile pour parser et tests

CXX = g++
CXXFLAGS = -std=c++11 -Wall

# fichiers sources
SRCS = main.cpp lexer.cpp symbole.cpp automate.cpp state.cpp
OBJS = $(SRCS:.cpp=.o)

# fichiers sources pour les tests
TEST_SRCS = Tests.cpp lexer.cpp symbole.cpp automate.cpp state.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# cible par défaut
 
all: parser

 
# parser principal
 
parser: $(OBJS)
	$(CXX) -o parser $(OBJS)

 
# compilation des .o
 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<


# tests

tests: $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) -o tests $(TEST_SRCS)


# nettoyage
clean:
	rm -f *.o parser tests