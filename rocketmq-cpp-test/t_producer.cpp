/*
* Description: Simple Producer demo
*/
 
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "CProducer.h"
#include "CMessage.h"
#include "CSendResult.h"
 
using namespace std;
 
// send message
void StartSendMessage(CProducer *producer)
{
    CSendResult result;
 
    // create message and set some values for it
    CMessage *msg = CreateMessage("Test_Topic");
    SetMessageTags(msg, "Test_Tag");
    SetMessageKeys(msg, "Test_Keys");
    
    for (int i = 0; i < 10; i++)
    {
        // construct different body
        string strMessageBody = "this is body number-" + to_string(i);
        
        SetMessageBody(msg, strMessageBody.c_str());
        // send message
        SendMessageSync(producer, msg, &result);
 
        cout << "send message[" << i << "], result status:" << (int)result.sendStatus << ", msgBody:" << strMessageBody << endl;
    }
 
    // destroy message
    DestroyMessage(msg);
}
 
int main(int argc, char *argv[])
{
    cout << "Producer Initializing....." << endl;
    CProducer* producer;

    for(int i = 0; i < 100; i++) {
        // create producer and set some values for it
        producer = CreateProducer("Group_producer");
        SetProducerNameServerAddress(producer, "10.200.112.67:9876");
        // start producer
        StartProducer(producer);
        cout << "Producer start....." << endl;
        // send message
        StartSendMessage(producer);
        // shutdown producer
        ShutdownProducer(producer);
        // destroy producer
        DestroyProducer(producer);
        cout << "Producer Shutdown!" << endl;
        sleep(1);
    }
    
    return 0;
}
 
