#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gperftools/heap-checker.h>
#include <gperftools/profiler.h>


void LeakTwentyBytes() {
    HeapLeakChecker heap_checker("test_malloc");
    //ProfilerStart("cpup");
    char* a = (char*)malloc(20);
    char* b = (char*)malloc(20);
    while(0) {
        printf("a");
    }
    //free(a);
    //This will pass: it totes up 20 bytes allocated and 20 bytes freed
    //assert(heap_checker.BriefNoLeaks());  // doesn't detect that b is leaked
    //ProfilerStop();
    heap_checker.NoLeaks();
}

int main() {
    LeakTwentyBytes();
    return 0;
}
