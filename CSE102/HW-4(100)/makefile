all: clear clean compile run

compile: main.c
	@gcc -o test main.c

run:
	@./test


clean:
	@rm -f *.o
	@rm -f test
	@rm -f receipt.txt

clear:
	@clear
