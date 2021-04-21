#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<errno.h>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<pthread.h>

pthread_mutex_t LOCK;
cv::Mat img;
void* MatStreamStart(void*args);


int main(void){
    //init lock
    pthread_mutex_init(&LOCK,NULL);

    pthread_t MATSTREAM;
    int MATSTREAMID;
    char args;
    MATSTREAMID=pthread_create(&MATSTREAM,NULL,MatStreamStart,(void*)&args);
    sleep(5);
    cv::namedWindow("win",0);
    cv::Mat origin_img;
    while(1){
        pthread_mutex_lock(&LOCK);//lock
        if(img.empty()){std::cout<<"图像为空"<<std::endl;return -1;}
        origin_img=img.clone();
        pthread_mutex_unlock(&LOCK);//unlock
        printf("SHOW\n");
        cv::imshow("win",origin_img);
        char key=cv::waitKey(10);
        if(key=='q'){
            pthread_detach(MATSTREAM);
            pthread_join(MATSTREAM,NULL);
            pthread_mutex_destroy(&LOCK);
            return 0;
        }
    }
    //创建本机套接字,使用TCP协议
    int server_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(0>=server_socket){//创建套接字失败
        printf("create socket failed,errno\n");
        return -1;
    }
    //创建本机信息结构体
    struct sockaddr_in server_address;
    //结构体初始化为0
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=inet_addr("10.60.66.12");
    server_address.sin_port=htons(2222);
    //套接字绑定本机信息
    bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
    //监听
    listen(server_socket,20);
    //创建客户端信息结构体
    struct sockaddr_in client_address;
    socklen_t client_address_size=sizeof(client_address);
    //单线程接受请求
    while(1){
        //进行接受请求,获取客户端套接字client_socket
        int client_socket=accept(server_socket,(struct sockaddr*)&client_address,&client_address_size);
        
        //定义缓冲区
        char buffer[512]={0};
        size_t count=0;
        write(client_socket,buffer,count);//从buffer写入count字节到客户端套接字

        //写入完毕,关闭向客户端读写数据通道
        shutdown(client_socket,SHUT_WR);
        //关闭客户端的套接字
        close(client_socket);
        printf("处理完毕\n");
    }
    //关闭服务端的套接字
    close(server_socket);
    return 0;
}


void* MatStreamStart(void*args){
     static int count=0;
     printf("|*创建相机线程*|\n");
     cv::VideoCapture capture(0);
     if(capture.isOpened()==false){
         printf("|*创建相机线程失败<-:->相机没有启动*|\n");
         return args;
     }
     printf("|*相机线程创建成功*|\n");
     while(1){
        //lock
        pthread_mutex_lock(&LOCK);
        capture>>img;
        if(count>1000){
            count=0;
        }
        printf("%d\n",count++);
        //unlock
        pthread_mutex_unlock(&LOCK);
        usleep(10000);
     }
     printf("|*相机线程结束*|\n");
     return args;
 }
