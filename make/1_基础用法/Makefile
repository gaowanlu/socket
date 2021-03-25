main:hello.o world.o main.o
	gcc hello.o world.o main.o -o main 
hello.o:hello.h hello.c
	gcc -c hello.c
world.o:world.h world.c
	gcc -c world.c
main.o:main.c hello.h world.h
	gcc -c main.c
clean:
	rm *.o

#makefile中的命令必须要以tab键开始
