#include<stdio.h>
#include<pthread.h>
/*
 *创建线程
 *pthread_create(&thrd1, NULL, (void *)&thread_function, (void *) &some_argument);
 *              线程号  线程属性指针 调用函数指针           调用函数传递的参数
 *返回值是否创建线程成功
 *
 *结束线程
 *pthread_exit(void*retaval);//retval存储线程结束的状态
 *
 * 线程等待
 * pthread_join(pthread_t th,void** thread_return);
 *
 * 数据类型
 * pthread_t :线程ID
 * pthread_attr_t :线程属性
 * 
 *
 * */
void threadAFun(void*ptr){
    for(int i=0;i<100;i++){
        for(int j=0;j<99999;j++){

        }
        printf("Thread A\n");
    }
}
void threadBFun(void*ptr){
    for(int i=0;i<100;i++){
        for(int j=0;j<99999;j++){

        }
        printf("Thread B\n");
    }
}

int main(void){
    //创建线程A
    int threadAIP,threadBIP;
    pthread_t threadA,threadB;
    char *me="sfd";
    threadAIP=pthread_create(&threadA,NULL,(void*)&threadAFun,(void*)me);
    //创建线程B
    threadBIP=pthread_create(&threadB,NULL,(void*)&threadBFun,(void*)me);
    void*retavl;
    int temp1=pthread_join(threadB,&retavl);//阻塞
    int temp2=pthread_join(threadA,&retavl);
    return 0;
}
