
rm data/ -fr
mkdir data/

g++ --std=c++11 test.cpp -o run -lrocksdb
