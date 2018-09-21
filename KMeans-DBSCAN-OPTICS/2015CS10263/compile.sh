#!/bin/sh

mkdir -p bin
gcc -O3 -c kdtree.c -o bin/kdtree.o
g++ -O3 -c dbscan.cpp -std=c++14 -o bin/dbscan.o
g++ -O3 bin/kdtree.o bin/dbscan.o -o dbscan

g++ -std=c++14 -O3 -o optics optics.cpp
