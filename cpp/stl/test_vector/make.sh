#!/bin/bash

mkdir bin -p

g++ t_vector.cpp -o bin/delv
g++ -std=c++11 t_vector_api.cpp -o bin/api

