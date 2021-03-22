#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
int main(void){
   char filename[1000]={0};
   printf("使用文件名称\n");
   scanf("%s",filename);
   FILE* file=fopen(filename,"wb");
   if(!file){
       printf("open file failed,errno = %d\n",errno);
       return -1;
   }
   //创建本机套接字
   int client_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
   if(client_socket==-1){
       fclose(file);
       printf("socket faild ,errno = %d.\n",errno);
       return -1;
   }
   //主机地址信息
   struct sockaddr_in server_address;
   memset(&server_address,0,sizeof(server_address));
   server_address.sin_family=AF_INET;
   server_address.sin_addr.s_addr=inet_addr("10.60.66.157");
   server_address.sin_port=htons(1234);
   if(0!=connect(client_socket,(struct sockaddr*)&server_address,sizeof(server_address))){
       fclose(file);
       printf("connect failed,errno = %d.\n",errno);
       return -1;
   }
   //定义缓冲区
   char buffer[512]={0};
   size_t len;
   int temp=0;
   while(0!=(len=read(client_socket,buffer,512))){
       fwrite(buffer,len,1,file);
       if(temp%2==0){
           printf("*正在下载\n");
       }else{
           printf("#正在下载\n");
       }
       temp++;
       if(temp>10000)temp=0;
   }
   printf("file download success");
   fclose(file);
   close(client_socket);
   return 0;
}
