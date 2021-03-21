#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(void){
    /*创建套接字
     *AF_INET:IPV4
     *SOCK_STREAM:使用面向连接的数据传输方式
     *TPPROTO_TCP:表示使用TCP协议
     * */
    int serv_sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//本机套接字
    //将套接字和IP 端口绑定
    struct sockaddr_in serv_addr;
    //每个字节都用0填充
    memset(&serv_addr,0,sizeof(serv_addr));
    
    /*端口与IP信息存储在struct sockaddr数据类型
     * */

    //使用IPV4地址(AF_INET代表使用IPV4地址)
    serv_addr.sin_family=AF_INET;
    //具体ip地址
    serv_addr.sin_addr.s_addr=inet_addr("10.60.66.157");
    //端口
    serv_addr.sin_port=htons(1234);

    /*套接字与IP端口联系起来
     * */

    //套接字绑定ip与端口
    bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));


    /*进入监听状态,等待客户端发起请求*/
    listen(serv_sock,20);
    printf("监听进行中\n");

    /*接受客户端请求*/
    struct sockaddr_in clnt_addr;//存储客户端的IP与端口信息
    socklen_t clnt_addr_size=sizeof(clnt_addr);

    //不断的接受客户端请求
    while(1){
        int clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
        printf("接收到了请求\n");
        /*accept用来接受客户端请求,accept阻塞程序进行,直到接受到客户端请求
        *accept()返回客户端套接字
        * */
        
        //得到客户端的套接字cnlt_sock,从客户端的套接字读取信息
        char outData[1000];
        read(clnt_sock,outData,sizeof(outData)-1);
        printf("Message from Client:%s\n",outData);

        /*向客户端发送数据
        *使用write函数向套接字文件中写入文件,也就是向客户端发送文件
        *向客户端套接字写入东西
        */
        char str[1000];
        printf("请输入传给客户端的信息:");
        scanf("%s",str);
        write(clnt_sock,str,sizeof(str)-1);

        /*关闭套接字
         *因为套接字是一种文件,像普通文件一样,使用后应该关闭
        */
        close(clnt_sock);//关闭客户端的套接字
        printf("与客户端断开连接\n");
    }

    close(serv_sock);//关闭本机的套接字
    printf("程序结束\n");


    return 0;
}
