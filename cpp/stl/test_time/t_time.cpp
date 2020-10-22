#include <stdio.h>
#include <time.h>

int t_time() {
    /* time_t time(time_t* timer) */
    //same as `time_t now = time(NULL)`
    time_t now;
    time(&now);

    struct tm* t = NULL;
    /* struct tm* localtime(const time_t* timer) */
    t = localtime(&now);

    if(t == NULL) {
        return 0; 
    }

    // 设 t 为月初
    t->tm_hour = 0;
    t->tm_min = 0;
    t->tm_sec = 0;
    t->tm_mday = 1;

    /* double difftime(time_t end, time_t beginning) */
    double seconds = difftime(now, mktime(t));

    /* char* asctime(const struct tm* timeptr) */
    printf("%.f seconds have passed \nfrom %sto ", seconds, asctime(t));
    /* char* ctime(const time_t* timer) */
    printf("%s\n", ctime(&now));

    t = gmtime(&now);
    if(t == NULL) {
        return 0; 
    }
    printf("GMT：%2d:%02d\n", t->tm_hour, t->tm_min);

    time_t ret = mktime(t);
    char buffer[80] = {0};
    if(ret == -1) {
        printf("mktime error\n");
    }else {
        /* size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr) */
        strftime(buffer, sizeof(buffer), "%c", t);
        puts(buffer);
    }
    return 0;
}

int t_clock() {
    clock_t t;

    t = clock();
    for(long i=0; i< 10000000; i++) { }
    t = clock() - t;
    printf("t = %d(%f seconds)\n", t, ((float)t)/CLOCKS_PER_SEC);

    return(0);
}

int main() {
    t_time();
    t_clock();
    
    return 0;
}
