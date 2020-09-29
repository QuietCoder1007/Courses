program_NAME := lab06
program_CXX_SRCS := $(wildcard *.cpp)
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o}
CMAKE_BUILD_DEBUG := ./cmake-build-debug

CXX=clang++
CXXFLAGS = -g -std=c++11 -Wall

.PHONY: all clean

all: clean $(program_NAME)

$(program_NAME): $(program_CXX_OBJS)
	$(CXX) $(CXXFLAGS) $(program_CXX_OBJS) -o $(program_NAME)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_CXX_OBJS)
	
distclean: clean
	@- $(RM) -rf $(CMAKE_BUILD_DEBUG)