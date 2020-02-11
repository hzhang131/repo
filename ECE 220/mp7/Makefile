
mp7: main.c notmymp7.c
	g++ -g -c notmymp7.c -o notmymp7.o
	g++ -g -c main.c -o main.o
	g++ -g main.o notmymp7.o sudoku_golden.a -o mp7

clean:
	rm *.o mp7

sudoku1: mp7
	./mp7 sudoku1.txt

sudoku2: mp7
	./mp7 sudoku2.txt

sudoku3: mp7
	./mp7 sudoku3.txt
