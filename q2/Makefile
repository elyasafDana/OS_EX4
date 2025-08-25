CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic


all: run


main: Main.o Algorithms.o Graph.o
	$(CXX) $(CXXFLAGS) $^ -o $@

Main.o: Main.cpp Algorithms.hpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c $<

Algorithms.o: Algorithms.cpp Algorithms.hpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c $<

Graph.o: Graph.cpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c $<

run: main
	./main

# ניקוי
clean:
	rm -f *.o main

.PHONY: all run clean
