# ===== OS Project: TCP server/client build =====
CXX := g++
CXXFLAGS := -std=gnu++17 -O2 -Wall -Wextra -Wpedantic
LDFLAGS_SERVER := -pthread
LDFLAGS_CLIENT :=

# Sources
SRCS_SERVER := server.cpp Graph.cpp Algorithms.cpp
SRCS_CLIENT := client.cpp
HDRS := Graph.hpp Algorithms.hpp

# Binaries
BIN_SERVER := server
BIN_CLIENT := client

.PHONY: all clean run-server run-client

all: $(BIN_SERVER) $(BIN_CLIENT)

$(BIN_SERVER): $(SRCS_SERVER) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ server.cpp Graph.cpp Algorithms.cpp $(LDFLAGS_SERVER)

$(BIN_CLIENT): $(SRCS_CLIENT) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ client.cpp $(LDFLAGS_CLIENT)

clean:
	rm -f $(BIN_SERVER) $(BIN_CLIENT)


PORT ?= 8080
IP ?= 127.0.0.1

run-server: $(BIN_SERVER)
	./$(BIN_SERVER) $(PORT)

run-client: $(BIN_CLIENT)
	./$(BIN_CLIENT) $(IP) $(PORT)
