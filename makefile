all: sudoku

sudoku: main.o
	g++ main.o -o sudoku

main.o: main.cpp
	g++ -c main.cpp -o main.o

test_%: sudoku
	cat $@ | ./sudoku

tests: test_01 test_02 test_03 test_04

clean:
	rm -f main.o sudoku
