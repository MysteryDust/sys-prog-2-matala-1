C = g++
FLAGS = -std=c++17 -Wall -Wextra -g
VALGRIND = valgrind --leak-check=full
TARGET = Main
TEST_TARGET = test

# Source and header files
SOURCES = graph.cpp algorithms.cpp main.cpp
HEADERS = graph.h algorithms.h

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
MAIN_OBJ = main.o
LIB_OBJS = graph.o algorithms.o

# Test sources and test objects
TEST_SOURCES = tests.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Default build
all: $(TARGET)

Main: $(TARGET)

# Rule to link the main program
$(TARGET): $(OBJECTS)
	$(C) $(FLAGS) -o $(TARGET) $(OBJECTS)

# Compile all object files
%.o: %.cpp $(HEADERS)
	$(C) $(FLAGS) -c $< -o $@

# Rule to build the unit test executable
$(TEST_TARGET): $(TEST_OBJECTS) $(LIB_OBJS)
	$(C) $(FLAGS) -o $(TEST_TARGET) $(TEST_OBJECTS) $(LIB_OBJS)

# Run main
run: $(TARGET)
	./$(TARGET)

# Run unit tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Memory check with valgrind
valgrind: $(TARGET)
	$(VALGRIND) ./$(TARGET)

# Clean up all built files
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJECTS) $(TEST_OBJECTS)

.PHONY: all Main run test valgrind clean
