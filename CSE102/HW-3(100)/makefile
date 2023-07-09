all: clear clean compile run

compile: main.c
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test main.c

run:
	@echo "-------------------------------------------"
	@echo "Running the Program...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Program finished...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
clear:
	@clear