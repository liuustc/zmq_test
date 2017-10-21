
#include "./include/zmq.h"
#include "./include/zmq_utils.h"            //Zeromq 函数的导入在这里帮我们实现了
#include "string.h"
#include "unistd.h"

int main()
{
        void* context = zmq_ctx_new();
        void* zmq_reciever = zmq_socket(context, ZMQ_DEALER);

        if(!zmq_reciever)
            printf("Reciever init failed\n");

        const char* port = "tcp://127.0.0.1:5233";
        if(zmq_bind(zmq_reciever, port) >= 0)
            printf("reciever bind at %s\n", port);
        else
        {
            printf("reciever bind error\n");
            zmq_ctx_destroy(context);
            zmq_close(zmq_reciever);
            return 1;
        }

        int recvn=1;

        printf("starting...\n");
        while(1)    //循环工作
        {
            //接受部分
            char msg2recv[128] = {0};
            if(zmq_recv(zmq_reciever, &msg2recv, sizeof(msg2recv), 0) >= 0)
            {
                printf("第%d次收到client信息：%s\n", recvn++, msg2recv);
            }
            usleep(5e4);
        }
        zmq_close(zmq_reciever);
        zmq_ctx_destroy(context);

        return 0;
}
