# ===== Project Makefile (no .d files) =====

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
LDLIBS   := -pthread

# קבצי מקור משותפים (אלגוריתמים, גרף, UnionFind)
SRCS_COMMON := Graph.cpp Algorithms.cpp UnionFind.cpp
OBJS_COMMON := $(SRCS_COMMON:.cpp=.o)

# מטרות ברירת מחדל
.PHONY: all
all: server client

# ===== Targets =====

server: server.o $(OBJS_COMMON)
	$(CXX) $^ -o $@ $(LDLIBS)

client: client.o
	$(CXX) $^ -o $@ $(LDLIBS)

# חוק כללי ליצירת אובייקטים
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===== Utility targets =====

.PHONY: run-server run-client clean

run-server: server
	./server

run-client: client
	./client

clean:
	rm -f server client *.o
