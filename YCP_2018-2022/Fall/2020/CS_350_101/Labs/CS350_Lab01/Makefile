CXX=clang++
CXXFLAGS = -g -std=c++11 -Wall

SRCS = Histogram.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

lab01 : clean $(OBJS)
	$(CXX) -o $@ $(OBJS)

Histogram.o : Histogram.cpp Histogram.h

main.o : main.cpp Histogram.h

memcheck: lab01
	valgrind --tool=memcheck --gen-suppressions=all --leak-check=full --leak-resolution=med --track-origins=yes ./lab01

clean :
	rm -f *.o *.exe lab01
	
distclean: clean
	rm -rf ./cmake-build-debug
