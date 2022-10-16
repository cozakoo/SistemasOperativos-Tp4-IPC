#
all: servidor cliente


cliente: cliente.o comunicaciones.o hardware.o
	gcc -o cliente servidor.o comunicaciones.o hardware.o


servidor: servidor.o comunicaciones.o hardware.o
	gcc -o servidor servidor.o comunicaciones.o hardware.o

servidor.o: servidor.c servidor.h interfaz.h comunicaciones.h
	gcc -c servidor.c
	

comunicaciones.o: comunicaciones.c hardware.h comunicaciones.h
	gcc -c comunicaciones.c

hardware.o: hardware.c hardware.h
	gcc -c hardware.c
	
clean:
	rm hardware.o comunicaciones.o cliente cliente.o servidor.o servidor
