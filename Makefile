maze: maze.o
	g++ maze.o -o maze

maze.o: maze.cpp
	g++ -c maze.cpp

clean:
	rm *.o maze
