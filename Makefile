# Compiler
CC=g++

# Sources
SRC=solution.cc                   \
    sources/condition_variable.cc \
    sources/mutex.cc              \
    sources/thread.cc             \
    sources/thread_pool.cc        \

# Target executable
TARGET=solution

# Includes
INCLUDES=-I. -I/usr/include/ -I./includes

# Compilation flags
CFLAGS=-std=c++11 -g -Wall -fpermissive

# Librarary locations
LFLAGS=-L/usr/lib

# Dependencies
LIBS = -lpthread

# Object files
OBJS=$(SRC:.cc=.o)

all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET) $(LFLAGS) $(LIBS)

# Compilation rule
.cc.o: $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm $(TARGET) $(OBJS)

