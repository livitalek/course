all:
	gcc -fPIC addressbook.c -c
	gcc -shared addressbook.o -o libaddressbook.so
	gcc -rdynamic -o main main.c -ldl

lib:
	rm -rf *.o *.so
	gcc -fPIC addressbook.c -c
	gcc -shared addressbook.o -o libaddressbook.so

run:
	rm -rf main
	gcc -rdynamic -o main main.c -ldl

clean:
	rm -rf *.o *.so main