CLIBS=-lmuduo_net -lmuduo_base
CFLAGS=-pthread

main: main.cc server.o sudoku.o
	g++ main.cc server.o sudoku.o -o server $(CLIBS) $(CFLAGS) && rm *.o

server.o: server.cc sudoku.o
	g++ -c server.cc sudoku.o $(CLIBS) $(CFLAGS)

sudoku.o: sudoku.cc
	g++ -c sudoku.cc

clean:
	rm *.o