#!/bin/bash

mkdir -p bin

#g++ test_pqxx.cpp -o bin/pqxx -lpqxx -L/usr/local/pgsql/lib -lpq

g++ test_libpq.cpp -o bin/libpq -I/usr/local/pgsql/include -L/usr/local/pgsql/lib -lpq
