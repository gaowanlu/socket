#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(void){
    while(1){
        system("sudo /media/pi/DIST/socket/login/main");
        printf("请求成功\n");
        sleep(3);
    }
    return 0;
}
