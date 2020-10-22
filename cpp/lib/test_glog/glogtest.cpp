#include <iostream>
#include <glog/logging.h>

int main(int argc, char** argv) {
    FLAGS_alsologtostderr = 1;
    FLAGS_log_dir = "./logdir/";
    google::InitGoogleLogging(argv[0]);
    
    LOG(INFO) << "Info: xxxxxxxxxx";
    LOG(WARNING) << "Warning: xxxxxxxxxx";
    LOG(ERROR) << "Error: xxxxxxxxxx";
    LOG(FATAL) << "Fatal: xxxxxxxxxx";
     
    return 0;
}
