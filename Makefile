stupidos: stupidOS.o FileSystem.o
	g++ -g -Wall stupidOS.o FileSystem.o -o stupidos

stupidOS.o: queue_Wolfe.hpp LinkedList.hpp
	g++ -g -Wall -c stupidOS.cpp

FileSystem.o: FileSystem.h FileSystem.cpp
	g++ -g -Wall -c FileSystem.cpp

clean:
	rm *.o stupidos -v

remake: clean
	make stupidos
