.default: all

all: Assignment1

clean:
	rm -f Assignment1 *.o

Assignment1: Breadcrumb.o MazeSolver.o Trail.o main.o
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

%.a: %.cpp
	g++ -Wall -Werror -std=c++14 -O -c $^