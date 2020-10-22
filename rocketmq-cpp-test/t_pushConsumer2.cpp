#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "CPushConsumer.h"
#include "CMessageExt.h"

using namespace std;

int doConsumeMessage(struct CPushConsumer *consumer, CMessageExt *msgExt) {
    printf("Topic:%s, Body:%s\n", GetMessageTopic(msgExt), GetMessageBody(msgExt));
    return E_CONSUME_SUCCESS;
}

int main(int argc, char *argv[]) {
    CPushConsumer *consumer = CreatePushConsumer("Group_Consumer_Test");
    SetPushConsumerNameServerAddress(consumer, "127.0.0.1:9876");

    Subscribe(consumer, "T_TestTopic", "*");
    RegisterMessageCallback(consumer, doConsumeMessage);

    StartPushConsumer(consumer);

    for (int i = 0; i < 6; i++) {
        sleep(10);
    }

    ShutdownPushConsumer(consumer);
    DestroyPushConsumer(consumer);

    return 0;
}
