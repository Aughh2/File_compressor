CC = g++
CFLAGS = -Wall -Wextra -O2 -std=c++17
SRCS = main.cpp huffman.cpp file_database.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = file_compressor

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lsqlite3

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
