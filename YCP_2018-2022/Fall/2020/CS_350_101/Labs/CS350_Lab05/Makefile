CXX=clang++
CXXFLAGS = -g -std=c++11 -Wall

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

lab05 : clean $(OBJS)
	$(CXX) -o $@ $(OBJS)

main.o : main.cpp

memcheck: lab05
	valgrind --tool=memcheck --gen-suppressions=all --leak-check=full --leak-resolution=med --track-origins=yes ./lab05

clean :
	rm -f *.o *.exe lab05
	
distclean: clean
	rm -rf ./cmake-build-debug
