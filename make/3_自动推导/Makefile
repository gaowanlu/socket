ALL_O_FILE=hello.o world.o main.o
main:$(ALL_O_FILE)
	gcc $(ALL_O_FILE) -o main 
hello.o:hello.h hello.c
world.o:world.h world.c
main.o:main.c hello.h world.h
.PHONY:clean
clean:
	rm *.o main
