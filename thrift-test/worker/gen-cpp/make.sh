


g++ -g -Wall -I./ -I/usr/local/include/thrift WorkerManager.cpp worker_types.cpp worker_constants.cpp WorkerManager_server.skeleton.cpp -L/usr/local/lib/*.so -lthrift -std=c++11 -o server

g++ -g -Wall -I./ -I/usr/local/include/thrift WorkerManager.cpp worker_types.cpp worker_constants.cpp Client.cpp -L/usr/local/lib/*.so -lthrift -std=c++11 -o client
