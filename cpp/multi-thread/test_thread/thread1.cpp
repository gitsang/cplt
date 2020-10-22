#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

#define NUM_THREADS 5

void *say_hello(void *threadid) {
    int tid = *((int *)threadid);   //由无类型指针转为整形指针，并取内容
    cout << "hello, ID = " << tid << endl;
    return 0;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int indexes[NUM_THREADS];
    int rc; 
    int i;

    for(i = 0; i < NUM_THREADS; i++) {
        cout << "main() : creat thread " << i << endl;
        indexes[i]  = i;
        rc = pthread_create(&threads[i], NULL, say_hello, (void *)&(indexes[i]));   //传入的参数必须强转为void*类型

        if(rc) {    //线程创建成功返回0
            cout << "pthread_create error: error_code = " << rc << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL); //等待线程退出后，进程才结束
}
