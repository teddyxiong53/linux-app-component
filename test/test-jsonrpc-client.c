#include "jsonrpc_client.h"
#include "cJSON.h"
#include "mylog.h"

struct jrpc_client my_client;


pthread_t tid;

void * send_cmd_proc(void *arg)
{
    while (1) {
        sleep(2);
        jrpc_client_send_cmd_only_name(&my_client, "sayHello");
    }
}
int main(int argc, char const *argv[])
{
    int ret = 0;
    ret = jrpc_client_init(&my_client, "127.0.0.1", 1234);
    if (ret < 0) {
        myloge("client init fail");
        goto fail;
    }
    ret = jrpc_client_connect_server(&my_client);
    if (ret < 0) {
        myloge("connect to server fail");
        goto fail;
    }
    pthread_create(&tid, NULL, send_cmd_proc, NULL);
    mylogd("before run");
    jrpc_client_run(&my_client);
    mylogd("after run");
    jrpc_client_destroy(&my_client);
    return 0;
fail:
    jrpc_client_destroy(&my_client);
    return ret;
}

