CXXFLAGS=-std=gnu++11
all : example1

example1.lex.cpp : example1.l
	flex -o example1.lex.cpp example1.l
	sed -i- -e 's/register //g' example1.lex.cpp

example1.tab.hpp example1.tab.cpp : example1.ypp
	bison -d -o example1.tab.cpp example1.ypp

example1 : ast.cpp example1.lex.cpp example1.tab.cpp example1.tab.hpp
	$(CXX) $(CXXFLAGS) ast.cpp example1.lex.cpp example1.tab.cpp -o example1 $(LDFLAGS)


