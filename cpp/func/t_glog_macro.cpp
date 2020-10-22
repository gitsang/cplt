#include <iostream>
#include <gflags/gflags.h>
#include <glog/logging.h>

/* 
 * pre:
 *      mkdir log
 *
 * make:
 *      g++ t.cpp --std=c++11 -o r -lglog 
 */

#define LOGLEVEL    2 // only WARNING and ERROR can output
#define LOGLV(lv)   LOG_IF(INFO, LOGLEVEL <= lv)

int main(int argc, char* argv[]) {
    FLAGS_log_dir = "log";         
    google::InitGoogleLogging(argv[0]);

    LOG_IF(INFO, LOGLEVEL <= 1) << "NORMAL INFO level 1";

    LOGLV(2) << "WARNING INFO level 2";
    
    LOGLV(3) << "ERROR INFO level 3";

    return 0;
}
