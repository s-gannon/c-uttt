.PHONY: all clean
CXX=g++
CXXFLAGS=-Wall -pedantic
SRCS=main.cpp ttt.cpp uttt.cpp
OBJS=$(SRCS:.cpp=.o)
TARGET=cpp-uttt

all: $(TARGET)

cpp-uttt: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -- $(OBJS) $(TARGET)
