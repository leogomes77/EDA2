CC = gcc
CFLAGS = -Wall -g
OBJ = Cliente.o Meio_Mobilidade.o Gestor.o Aluger.o Grafo.o Main.o

all: projeto

projeto: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

Cliente.o: Cliente.c Cliente.h
	$(CC) $(CFLAGS) -c $<

Meio_Mobilidade.o: Meio_Mobilidade.c Meio_Mobilidade.h
	$(CC) $(CFLAGS) -c $<

Gestor.o: Gestor.c Gestor.h
	$(CC) $(CFLAGS) -c $<

Aluger.o: Aluger.c Aluger.h
	$(CC) $(CFLAGS) -c $<

Grafo.o: Grafo.c Grafo.h
	$(CC) $(CFLAGS) -c $<

Main.o: Main.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o projeto