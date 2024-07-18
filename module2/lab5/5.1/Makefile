all:
	gcc addressbook.c -c
	ar rc libaddressbook.a addressbook.o
	gcc -o main main.c -L . -laddressbook