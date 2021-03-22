#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<errno.h>
int main(void){
    //输入传输文件地址
    char *filename="./data.txt\0";
    printf("请输入要传输的文件:\n");
    //scanf("%s",filename);
    //文件指针(以读的方式打开)
    FILE* file=fopen(filename,"r");
    if(!file){
        printf("open file failed,errno = %d.\n",errno);
        return -1;
    }
    //创建本机套接字
    int server_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(0>=server_socket){
        fclose(file);
        printf("create socket failed,errno = %d.\n",errno);
        return -1;
    }
    //创建本机信息结构体
    struct sockaddr_in server_address;
    //结构体初始化为0
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=inet_addr("10.60.66.157");
    server_address.sin_port=htons(1234);
    //套接字绑定本机信息
    bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
    //监听
    listen(server_socket,20);
    //创建客户端信息结构体
    struct sockaddr_in client_address;
    socklen_t client_address_size=sizeof(client_address);
    while(1){
    //进行接受请求,获取客户端套接字client_socket
    int client_socket=accept(server_socket,(struct sockaddr*)&client_address,&client_address_size);
    printf("接受请求\n");
    //定义缓冲区
    char buffer[512]={0};
    size_t count;
    while((count=fread(buffer,1,512,file))>0){
        write(client_socket,buffer,count);
    }
    //关闭向客户端读写数据通道
    shutdown(client_socket,SHUT_WR);
    printf("受理成功\n");
    //关闭文件
    fclose(file);
    //关闭服务端与客户端的套接字
    close(client_socket);
    FILE* file=fopen(filename,"r");
    }
    close(server_socket);
    printf("Over!");
    return 0;
}
