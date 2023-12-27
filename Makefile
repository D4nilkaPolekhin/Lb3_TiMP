.PHONY: test clean

CXX = g++ -std=c++17

CXXFLAGS = -Wall -lboost_program_options -lcrypto++ -lUnitTest++

TARGET = Utest

SOURCES = test.cpp

OBJECTS = $(SOURCES:.cpp=.o)

DEPS = includer.h

test: $(TARGET) 
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) -o $(TARGET) 

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
