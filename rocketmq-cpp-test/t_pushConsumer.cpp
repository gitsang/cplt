/*
* Description: Simple push consumer demo
*/
 
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "CPushConsumer.h"
#include "CMessageExt.h"
 
using namespace std;
 
// consume message
int doConsumeMessage(struct CPushConsumer *consumer, CMessageExt *msgExt)
{
    cout << "[Consume Message] " << "MsgTopic:" << GetMessageTopic(msgExt) << ", MsgTags:" << GetMessageTags(msgExt)
        << ", MsgKeys:" << GetMessageKeys(msgExt) << ", MsgBody:" << GetMessageBody(msgExt) << endl;
 
    return E_CONSUME_SUCCESS;
}
 
int main(int argc, char *argv[])
{
    cout << "Push consumer Initializing...." << endl;
    // create push consumer and set some values for it
    CPushConsumer *consumer = CreatePushConsumer("Group_Consumer_Test");
    SetPushConsumerNameServerAddress(consumer, "127.0.0.1:9876;127.0.0.1:9877");
    Subscribe(consumer, "Test_Topic", "*");
    // register message callback
    RegisterMessageCallback(consumer, doConsumeMessage);
    // start push consumer
    StartPushConsumer(consumer);
    cout << "Push consumer start, and listening message within 1min..." << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << "Already Running: " << (i * 10) << "S" << endl;
        usleep(10000000);
    }
    // shutdown push consumer
    ShutdownPushConsumer(consumer);
    // destroy push consumer
    DestroyPushConsumer(consumer);
    cout << "PushConsumer Shutdown!" << endl;
    
    return 0;
}
 
