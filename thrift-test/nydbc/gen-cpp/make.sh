
# server
g++ -g -Wall -I./ -I/usr/local/include/thrift nydbc.cpp nydbc_types.cpp nydbc_constants.cpp nydbc_server.skeleton.cpp -L/usr/local/lib/*.so -lthrift -std=c++11 -o server

# client
#g++ -g -Wall -I./ -I/usr/local/include/thrift nydbc.cpp nydbc_types.cpp nydbc_constants.cpp Client.cpp -L/usr/local/lib/*.so -lthrift -std=c++11 -o client
