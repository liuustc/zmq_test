//zeromp 通讯测试server 端
#include "./include/zmq.h"
#include "./include/zmq_utils.h"            //Zeromq 函数的导入在这里帮我们实现了
#include "string.h"
#include <iostream>
#include "unistd.h"

int main()
{
        void* context = zmq_ctx_new();    //指定zmq 处理I/0事件的thread pool 为1
        void* z_s1 = zmq_socket(context, ZMQ_DEALER);

        if(!z_s1)
            printf("Sender init failed\n");

        const char* port = "tcp://127.0.0.1:5233";
        if(zmq_connect(z_s1, port) >= 0)
            printf("sender connect at %s\n", port);
        else
        {
            printf("sender connect failed\n");
            zmq_close(z_s1);
            zmq_ctx_destroy(context);
            return 1;
        }
        int recvn=1;

        printf("starting...\n");
        while(1)    //循环工作
        {
            //发送部分
            char msg2send[128] = {0};
            snprintf(msg2send, sizeof(msg2send), "a message: %d", recvn);
            const int len = strlen(msg2send);
            if(zmq_send(z_s1, msg2send, len, 0) >= 0)
                printf("%d.message send!\n", recvn++);
            sleep(1);

        }
        zmq_close(z_s1);
        zmq_ctx_destroy(context);

        return 0;
}
