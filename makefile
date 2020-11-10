#makefile
main: *.c
	gcc -o main *.c -Wall

.PHONY:clean
clean:
    rm -rf *.o test