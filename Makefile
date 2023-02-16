# CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra `pkg-config --cflags opencv4`
LDLIBS = `pkg-config --libs opencv4`

SRC = PerlinTest.cpp
OBJ = $(SRC:.cpp=.o)
BIN = PerlinTest

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(BIN) $(OBJ)