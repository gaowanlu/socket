#像C语言一样,#include别的文件
#ALL_O_FILE=hello.o world.o main.o
#Error: ALL_O_FILE=*.o
ALL_O_FILE=hello.o world.o main.o
main:$(ALL_O_FILE)
	gcc $(ALL_O_FILE) -o main 
-include Makefile.mk
hello.o:hello.h hello.c
world.o:world.h world.c
# var:=$(wildcard *.o)
main.o:$(wildcard he*.o) $(wildcard wo*.i)
.PHONY:clean
clean:
	-rm main $(ALL_O_FILE)
