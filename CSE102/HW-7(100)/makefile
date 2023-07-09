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
	@echo "In order to obey the rules specified in pdf file"
	@echo "Stack size of the terminal must be set to 16Mb"
	@echo "Setting stack size to 16Mb..."
	@echo "-------------------------------------------------"
	@ulimit -s 16384 && ./test
