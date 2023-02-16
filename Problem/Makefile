# CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra `pkg-config --cflags opencv4`
LDLIBS = `pkg-config --libs opencv4`

SRC = perlin.cpp
OBJ = $(SRC:.cpp=.o)
BIN = perlin

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(BIN) $(OBJ)