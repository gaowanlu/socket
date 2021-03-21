#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main(void){

        while(1){
        //创建套接字
        int sock=socket(AF_INET,SOCK_STREAM,0);
        //向服务器(特定IP和端口)发起请求
        struct sockaddr_in serv_addr;
        //每个字节都用0填充
        memset(&serv_addr,0,sizeof(serv_addr));
        //使用IPV4地址
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=inet_addr("10.60.66.157");
        //端口
        serv_addr.sin_port=htons(1234);


        //向本机的套接字写入信息,然后将本机套接字送给服务端
        if(1){
                /*connect()向服务器发送请求直到服务器传回数据后connect才结束
                 * */
                printf("\n连接服务器等待响应......\n");
                connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

                char inputData[1000];
                printf("请输入传给服务器的信息:");
                scanf("%s",inputData);
                printf("发送信息:%s",inputData);
                //将inputData写入到本机的套接字
                write(sock,inputData,strlen(inputData)+1);
        }


        //读取服务器传回的数据
        char buffer[1000];
        read(sock,buffer,sizeof(buffer)-1);//从本机得套接读取内容因为服务端操纵了本机套接字
        printf("Message from Server:%s\n",buffer);



        //关闭套接字
        close(sock);

        }
        return 0;
}
