all:
	g++ *.cpp -o main -g
	./main exp.in exp.out
	cat exp.out
