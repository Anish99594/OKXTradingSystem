CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -Ilib/websocketpp -I/usr/local/opt/boost/include
LDFLAGS = -L/usr/local/opt/boost/lib -lcurl -lpthread -lboost_system -lboost_thread-mt

SRCS = src/main.cpp src/order_management.cpp src/websocket_server.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = OKXTradingSystem

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
