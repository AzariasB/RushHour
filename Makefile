CXX = g++
CXXFLAGS = -std=c++17

SOURCES = src/main.cpp \
          src/Car.cpp \
          src/Map.cpp \
          src/State.cpp

HEADERS = src/Car.hpp \
          src/Map.hpp \
          src/Point.hpp \
          src/State.hpp

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = rushhour

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
