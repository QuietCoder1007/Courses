CXX=clang++
CXXFLAGS = -g -std=c++11 -Wall

SRCS = Histogram.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

lab03: clean $(OBJS)
	$(CXX) -o $@ $(OBJS)

Histogram.o : Histogram.cpp Histogram.h

main.o : main.cpp Histogram.h

memcheck: lab03
	valgrind --tool=memcheck --gen-suppressions=all --leak-check=full --leak-resolution=med --track-origins=yes ./lab03

clean :
	rm -f *.o *.exe lab03
	
distclean: clean
	rm -rf ./cmake-build-debug
