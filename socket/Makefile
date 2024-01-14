CXX = g++
ifeq ($(OS), Windows_NT)
	CXXFLAGS = -std=c++17 -lwsock32
else
	CXXFLAGS = -std=c++17
endif
BUILD_DIR = build

all: server client

server: src/server.cpp
	$(CXX) $^ -o $(BUILD_DIR)/$@ $(CXXFLAGS)

client: src/client.cpp
	$(CXX) $^ -o $(BUILD_DIR)/$@ $(CXXFLAGS)

clean:
ifeq ($(OS), Windows_NT)
	del /Q $(BUILD_DIR)\*
else
	rm -rf $(BUILD_DIR)/*
endif
