SRC_DIR = src/
BIN_DIR = bin/
OBJ_DIR = obj/
HEAD_DIR = headers/

CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -g

OFILES = 	${OBJ_DIR}card.o \
			${OBJ_DIR}board.o \
			${OBJ_DIR}interface.o \
			${OBJ_DIR}structures.o \
			${OBJ_DIR}main.o 
			
OFILES_TEST = ${OBJ_DIR}test.o

but : main

${OBJ_DIR}test.o : ${SRC_DIR}test.c
					$(CC) $(CFLAGS)  -o ${OBJ_DIR}test.o -c ${SRC_DIR}test.c

${OBJ_DIR}main.o : ${SRC_DIR}main.c
					$(CC) $(CFLAGS)  -o ${OBJ_DIR}main.o -c ${SRC_DIR}main.c

${OBJ_DIR}card.o : ${SRC_DIR}card.c
					$(CC) $(CFLAGS) -o ${OBJ_DIR}card.o -c ${SRC_DIR}card.c

${OBJ_DIR}board.o : ${SRC_DIR}board.c
					$(CC) $(CFLAGS)  -o ${OBJ_DIR}board.o -c ${SRC_DIR}board.c

${OBJ_DIR}structures.o : ${SRC_DIR}structures.c
					$(CC) $(CFLAGS) -o ${OBJ_DIR}structures.o -c ${SRC_DIR}structures.c

${OBJ_DIR}interface.o : ${SRC_DIR}card.c ${SRC_DIR}interface.c 
					$(CC) $(CFLAGS) -o ${OBJ_DIR}interface.o -c ${SRC_DIR}interface.c

main : ${OFILES}
	$(CC) $(CFLAGS) -o ${BIN_DIR}main ${OFILES}

test : ${OFILES}
	$(CC) $(CFLAGS) -o ${BIN_DIR}test  ${OFILES} ${OFILES_TEST}; ./${BIN_DIR}test

clean :
	-rm -f ${OFILES} ${BIN_DIR}main

play : main
		clear;./${BIN_DIR}main

.PHONY : but clean play test
