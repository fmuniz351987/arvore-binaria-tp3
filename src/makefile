CC = g++
CFLAGS = -Wall -pedantic -std=c++14 -g3

../pesquisa: main.o
	$(CC) $(CFLAGS) -o ../pesquisa arvore.o main.o

main.o: main.cpp arvore.o
	$(CC) $(CFLAGS) -c main.cpp

arvore.o: arvore.cpp arvore.hpp
	$(CC) $(CFLAGS) -c arvore.cpp

clean:
	rm ../pesquisa *.o
