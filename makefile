CFLAGS = -g -Wall -Werror -Wconversion -std=c99
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

evento_pesca: evento_pesca.c main.c
	gcc evento_pesca.c main.c $(CFLAGS) -o evento_pesca

exe: evento_pesca
	clear
	./evento_pesca arrecife.txt acuario.txt

debug: evento_pesca
	gdb ./evento_pesca

test: evento_pesca
	valgrind $(VFLAGS) ./evento_pesca