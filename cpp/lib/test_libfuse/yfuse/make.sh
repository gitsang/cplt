#!/bin/bash

ps aux | grep yfuse | grep -v grep | awk '{print $2}' | xargs -i -t kill -9 {}

rm yfuse

g++ main.cpp -o yfuse --std=c++11 -D_FILE_OFFSET_BITS=64 -lfuse3 -lboost_system -lcurl
