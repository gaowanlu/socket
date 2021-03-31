# 文件搜索
# 当项目大的时候,不可能把所有代码放在同一个文件夹下面
# Makefile文件中有一个特殊变量VPATH,make只会在当前目录中寻找依赖文件

VPATH=src:hfile
#搜索优先级 当前位置->./src->./hfile
ALL_O_FILE=hello.o world.o main.o
main:$(ALL_O_FILE)
	gcc $(ALL_O_FILE) -o main 
hello.o:hello.h hello.c
world.o:world.h world.c
main.o:main.c hello.h world.h
.PHONY:clean
clean:
	-rm main *.o
