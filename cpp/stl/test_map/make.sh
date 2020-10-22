#!/bin/bash

mkdir -p bin

g++ t_map.cpp -o bin/map
g++ t_bound.cpp -o bin/bound
g++ t_compare.cpp -o bin/comp
