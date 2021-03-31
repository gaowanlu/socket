# 使用vpath,比VPATH更加灵活

# 三种方式
# vpath <pattern> <directories>
# 为符合模式<pattern>的文件指定搜索目录<directories>

# vpath <pattern>
# 清除符合模式<pattern>的文件的搜索目录

# vpath
# 清除所有已被设置好了的文件搜索目录




# vpath %.c src:...:..
vpath %.c src
vpath %.h hfile
ALL_O_FILE=hello.o world.o main.o
main:$(ALL_O_FILE)
	gcc $(ALL_O_FILE) -o main 
hello.o:hello.h hello.c
world.o:world.h world.c
main.o:main.c hello.h world.h
.PHONY:clean
clean:
	-rm main *.o
