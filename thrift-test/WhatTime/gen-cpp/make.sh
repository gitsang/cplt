
# server
g++ -g -Wall -I./ -I/usr/local/include/thrift TimeService.cpp WhatTime_types.cpp WhatTime_constants.cpp server.cpp -L/usr/local/lib/*.so -o server -lthrift -std=c++11

# client
g++ -g -Wall -I./ -I/usr/local/include/thrift TimeService.cpp WhatTime_types.cpp WhatTime_constants.cpp client.cpp -L/usr/local/lib/*.so -o client -lthrift -std=c++11
