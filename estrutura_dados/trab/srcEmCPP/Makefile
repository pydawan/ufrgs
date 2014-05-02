# verificador-ortografico.out eh o programa principal. depende dos objetos grafos.o e arvores.o
verificador-ortografico : grafos.o arvores.o main.o mylib.o
	g++ -o verificador-ortografico main.o grafos.o arvores.o mylib.o

grafos.o : grafos.cpp mylib.h
	g++ -c grafos.cpp

main.o : main.cpp main.h
	g++ -c main.cpp

arvores.o : arvores.cpp mylib.h
	g++ -c arvores.cpp

mylib.o : mylib.cpp mylib.h
	g++ -c mylib.cpp

clean : 
	rm *.o verificador-ortografico
