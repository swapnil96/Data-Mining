#!/bin/sh

km="-kmeans"
db="-dbscan"
op="-optics"
ck="-check"
echo $2
if [ "$1" = "$km" ]
then
    ./kmeans $2 $3
elif [ "$1" = "$db" ]
then
    ./dbscan $2 $3 $4
    # for x in `seq 1 100`
    # do
    #     echo $x
    #     ./apriori $1 $x t1 0
    #     ./fptree $1 $x t2 0
    #     python check.py t1.txt t2.txt >> ans.txt 
    # done
elif [ "$1" = "$op" ]
then
    ./optics $2 $3 $4 > reach.txt
    python plot.py reach.txt
else
    python generate.py
fi