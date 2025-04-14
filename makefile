EXEC = Mcsansano
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g
SRC = main.c tablero.c inventario.c acciones.c
OBJ = $(SRC:.c=.o)
HEADERS = main.h tablero.h inventario.h acciones.h

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f $(OBJ) $(EXEC)

clean-o:
	rm -f $(OBJ)
