
//zeromp 通讯测试server 端
#include "./include/zmq.h"
#include "./include/zmq_utils.h"            //Zeromq 函数的导入在这里帮我们实现了
#include "string.h"
#include <iostream>
#include "unistd.h"

int main()
{
        void* context = zmq_ctx_new();    //指定zmq 处理I/0事件的thread pool 为1
        void* z_s2 = zmq_socket(context, ZMQ_DEALER);

        if(!z_s2)
            printf("Reciever init failed\n");

        const char* port = "tcp://127.0.0.1:5233";
        if(zmq_bind(z_s2, port) >= 0)
            printf("reciever bind at %s\n", port);
        else
        {
            printf("reciever bind error\n");
            zmq_ctx_destroy(context);
            zmq_close(z_s2);
            return 1;
        }

        int recvn=1;

        printf("starting...\n");
        while(1)    //循环工作
        {
            //接受部分
            char msg2recv[128] = {0};
            if(zmq_recv(z_s2, &msg2recv, sizeof(msg2recv), 0) >= 0)
            {
                std::cout<<"第\t"<<recvn++<<"\t次收到client信息：\t";
                std::cout<< msg2recv <<std::endl;
            }

            sleep(1);
        }
        zmq_close(z_s2);
        zmq_ctx_destroy(context);

        return 0;
}
