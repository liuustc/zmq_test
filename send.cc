#include "./include/zmq.h"
#include "./include/zmq_utils.h"            //Zeromq 函数的导入在这里帮我们实现了
#include "string.h"
#include "unistd.h"

int main()
{
        void* context = zmq_ctx_new();
        void* zmq_sender = zmq_socket(context, ZMQ_DEALER);

        if(!zmq_sender)
            printf("Sender init failed\n");

        const char* port = "tcp://127.0.0.1:5233";
        if(zmq_connect(zmq_sender, port) >= 0)
            printf("sender connect at %s\n", port);
        else
        {
            printf("sender connect failed\n");
            zmq_close(zmq_sender);
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
            if(zmq_send(zmq_sender, msg2send, len, 0) >= 0)
                printf("%d.message send!\n", recvn++);
            char msg2recv[256] = {'\0'};
            if(zmq_recv(zmq_sender, msg2recv, sizeof(msg2recv), 0) >= 0)
                printf("recieved reply: %s\n", msg2recv);

            sleep(1);
            if(recvn > 50)
                break;

        }
        zmq_close(zmq_sender);
        zmq_ctx_destroy(context);

        return 0;
}
