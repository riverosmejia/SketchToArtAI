CXX = g++
CXXFLAGS = -Iinclude -lboost_system -pthread -Wall -g
SRC = src/main.cpp \
      src/server.cpp \
      src/Routes/index_routes.cpp \
      src/Controllers/index_controllers.cpp \
      src/Controllers/ai_generateController.cpp \
      src/Services/ai_generateService.cpp \
      src/Controllers/ai_sketchController.cpp \
      src/Services/ai_sketchService.cpp

OBJ = $(SRC:.cpp=.o)
TARGET = server

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clear:
	rm -f $(OBJ) $(TARGET)
	