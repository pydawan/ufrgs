# verificador-ortografico.out eh o programa principal. depende dos objetos grafos.o e arvores.o
grafos-coloracao: caminhamentos.o main.o fila.o
	gcc -o grafos-coloracao main.o caminhamentos.o fila.o

caminhamentos.o : caminhamentos.c caminhamentos.h
	gcc -c caminhamentos.c

main.o : main.c
	gcc -c main.c

fila.o : fila.c fila.h
	gcc -c fila.c

clean : 
	rm *.o grafos-coloracao
