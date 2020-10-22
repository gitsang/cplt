#g++ -o consumer_example consumer_example.cpp -lrocketmq -lpthread -lz -ldl -lrt

g++ -o t_producer t_producer.cpp -I/root/package/rocketmq-client-cpp/include/ -L/root/package/rocketmq-client-cpp/bin -lrocketmq -lpthread -lz -ldl -lrt -std=c++11 

g++ -o t_pushConsumer t_pushConsumer.cpp -I/root/package/rocketmq-client-cpp/include/ -L/root/package/rocketmq-client-cpp/bin -lrocketmq -lpthread -lz -ldl -lrt -std=c++11 
g++ -o t_pushConsumer2 t_pushConsumer2.cpp -I/root/package/rocketmq-client-cpp/include/ -L/root/package/rocketmq-client-cpp/bin -lrocketmq -lpthread -lz -ldl -lrt -std=c++11 
