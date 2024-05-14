FLAGS = -Wall -lm

lectura.o: lectura.h lectura.c estructuras.h
	gcc -c $(FLAGS) lectura.c

filtros.o: filtros.h filtros.c estructuras.h
	gcc -c $(FLAGS) filtros.c

clasificacion.o: clasificacion.h clasificacion.c estructuras.h
	gcc -c $(FLAGS) clasificacion.c

resultados.o: resultados.h resultados.c
	gcc -c $(FLAGS) resultados.c

main: main.c lectura.o filtros.o clasificacion.o
	gcc $(FLAGS) -o main main.c lectura.o filtros.o clasificacion.o

clear:
	rm -f main *.o