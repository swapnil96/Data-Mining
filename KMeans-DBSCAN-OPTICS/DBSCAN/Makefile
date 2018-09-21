all:
	mkdir -p bin
	gcc -O3 -c kdtree.c -o bin/kdtree.o
	g++ -O3 -c dbscan.cpp -std=c++14 -o bin/dbscan.o
	g++ -O3 bin/kdtree.o bin/dbscan.o -o bin/out

clean:
	rm -rf bin