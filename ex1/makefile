all : ctp

ctp : ex1.c libListe.o libElt.o
	gcc ex1.c libListe.o libElt.o -o ex1

lib : libListe.o libElt.o

libListe.o : libListe.c
	gcc -c libListe.c

libElt.o : libElt.c
	gcc -c libElt.c

clean :
	rm *.o
