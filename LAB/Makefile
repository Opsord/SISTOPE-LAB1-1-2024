FLAGS = -Wall -lm

main: main.c lectura.o filtros.o clasificacion.o resultados.o
	gcc $(FLAGS) -o main main.c lectura.o filtros.o clasificacion.o resultados.o

lectura.o: lectura.h lectura.c estructuras.h
	gcc -c $(FLAGS) lectura.c

filtros.o: filtros.h filtros.c estructuras.h
	gcc -c $(FLAGS) filtros.c

clasificacion.o: clasificacion.h clasificacion.c estructuras.h
	gcc -c $(FLAGS) clasificacion.c

resultados.o: resultados.h resultados.c
	gcc -c $(FLAGS) resultados.c

clear:
	rm -f main *.o