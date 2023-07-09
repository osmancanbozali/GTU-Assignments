all: clear clean compile run

compile: main.c
	@gcc -o test main.c

clean:
	@rm -f *.o
	@rm -f test

clear:
	@clear

run:
	@echo "---------------------WARNING---------------------"
	@echo "Setting stack size to 64000 bytes..."
	@echo "-------------------------------------------------"
	@ulimit -s 64000 && ./test
