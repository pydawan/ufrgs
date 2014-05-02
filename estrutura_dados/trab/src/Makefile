# verificador-ortografico.out eh o programa principal. depende dos objetos grafos.o e arvores.o
verificador-ortografico : grafos.o arvores.o main.o mylib.o
	gcc -o verificador-ortografico main.o grafos.o arvores.o mylib.o

grafos.o : grafos.c mylib.h
	gcc -c grafos.c

main.o : main.c main.h
	gcc -c main.c

arvores.o : arvores.c mylib.h
	gcc -c arvores.c

mylib.o : mylib.c mylib.h
	gcc -c mylib.c

clean : 
	rm *.o verificador-ortografico
