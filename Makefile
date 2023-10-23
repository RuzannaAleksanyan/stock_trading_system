# Compiler and flags
CC = g++
CFLAGS = -Wall -std=c++11

# Source files
SRCS = main.cpp order_book.cpp order.cpp stock_trading_system.cpp stock.cpp test.cpp trader.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
HDRS = order_book.h order.h stock_trading_system.h stock.h test.h trader.h

# Executable name
TARGET = stock_trading_system

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
