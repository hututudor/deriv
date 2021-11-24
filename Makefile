all:
	g++ *.cpp -o main 
	./main exp.in exp.out
	cat exp.out
