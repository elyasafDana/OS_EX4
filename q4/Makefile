CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# ברירת מחדל: לקמפל ואז להריץ
all: run

# הלינק הסופי
main: Main.o Algorithms.o Graph.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# קומפילציית קבצים בודדים עם תלויות על ההדרים
Main.o: Main.cpp Algorithms.hpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c $<

Algorithms.o: Algorithms.cpp Algorithms.hpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c $<

Graph.o: Graph.cpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c $<

valgrind:
	valgrind --leak-check=full ./main -v 4 -e 4 -r 2

# להריץ את התוכנית
run: main
	./main

# ניקוי
clean:
	rm -f *.o main

.PHONY: all run clean valgrind
