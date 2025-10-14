CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = cipher
SOURCES = main.cpp modAlphaCipher.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
