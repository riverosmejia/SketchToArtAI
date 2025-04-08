CXX = g++
CXXFLAGS = -Iinclude -lboost_system -pthread -Wall -g
SRC = src/main.cpp src/server.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = server

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
	