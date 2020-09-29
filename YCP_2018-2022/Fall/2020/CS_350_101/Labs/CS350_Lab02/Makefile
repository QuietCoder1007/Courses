CXX=clang++
CXXFLAGS = -g -std=c++11 -Wall

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

lab02 : clean $(OBJS)
	$(CXX) -o $@ $(OBJS)

main.o : main.cpp

clean :
	rm -f *.o *.exe lab02
	
distclean: clean
	rm -rf ./cmake-build-debug
