all:
	gcc -fPIC src/*.c -c 
	mv *.o obj/
	gcc -shared obj/summation.o -o lib/libsummation.so
	gcc -shared obj/subtraction.o -o lib/libsubtraction.so
	gcc -shared obj/multiplication.o -o lib/libmultiplication.so
	gcc -shared obj/division.o -o lib/libdivision.so
	gcc -shared obj/power.o -o lib/libpower.so

	gcc -rdynamic -o main main.c -ldl

lib:
	rm -rf *.o *.so 
	gcc -fPIC src/*.c -c 
	mv *.o obj/
	gcc -shared obj/summation.o -o lib/libsummation.so
	gcc -shared obj/subtraction.o -o lib/libsubtraction.so
	gcc -shared obj/multiplication.o -o lib/libmultiplication.so
	gcc -shared obj/division.o -o lib/libdivision.so
	gcc -shared obj/power.o -o lib/libpower.so

run:
	rm -rf main
	gcc -rdynamic -o main main.c -ldl

clean:
	rm -rf *.o *.so main