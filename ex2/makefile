all : ctp

ctp : ex2.c libArbre.o libElt.o
	gcc libArbre.o libElt.o ex2.c -o ex2.exe

lib : libArbre.o libElt.o

libArbre.o : libArbre.c
	gcc -c libArbre.c

libElt.o : libElt.c
	gcc -c libElt.c

clean :
	rm *.o
