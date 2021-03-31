
# 多目标
# makefile规则中的目标可以不止一个
# 略 自动化变量  $@






vpath %.c src
vpath %.h hfile
ALL_O_FILE=hello.o world.o main.o
main:$(ALL_O_FILE)
	gcc $(ALL_O_FILE) -o main 
hello.o:hello.h hello.c
world.o:world.h world.c
main.o:main.c hello.h world.h
.PHONY:clean run
clean:
	-rm main *.o
run:
	sudo ./main


# 伪目标
# .PHONY:lable lable lable

