maze: maze.cpp
	g++ -Wall -Werror -std=c++14 maze.cpp -o maze

clean:
	rm *.o maze
