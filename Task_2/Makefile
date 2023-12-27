.PHONY: all clean

CXX = g++


CXXFLAGS = -Wall -lboost_program_options


TARGET = table_cipher


SOURCES = main.cpp table_cipher.cpp


OBJECTS = $(SOURCES:.cpp=.o)


DEPS = table_cipher.h


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) -o $(TARGET) 

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
