LEX = flex
YACC = bison
CC = gcc

a.out: main.o jack.tab.o lex.yy.o
	$(CC) main.o jack.tab.o lex.yy.o

jack.tab.o: jack.tab.c
	$(CC) -c jack.tab.c

jack.tab.c: jack.y
	$(YACC) -d jack.y

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c

lex.yy.c: jack.lex
	$(LEX) jack.lex

main.o: main.c
	$(CC) -c main.c

clean:
	rm -rf *.o jack.tab.c lex.yy.c a.out