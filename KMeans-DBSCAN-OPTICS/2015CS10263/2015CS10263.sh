#!/bin/sh

km="-kmeans"
db="-dbscan"
op="-optics"
ck="-check"
if [ "$1" = "$km" ]
then
    python2 kmeans.py $2 $3
elif [ "$1" = "$db" ]
then
    ./dbscan $2 $3 $4
elif [ "$1" = "$op" ]
then
    ./optics $2 $3 $4 > reach.txt
    python2 plot.py reach.txt
elif [ "$1" = "$ck" ]
then
    python2 kmeans.py 4 $2
    ./dbscan 40 0.7 $2
    ./optics 40 0.7 $2 70 > optics.txt
    python2 plot.py kmeans.txt $2 kmeans
    python2 plot.py dbscan.txt $2 dbscan
    python2 plot.py optics.txt $2 optics
else
    rm -rf bin
fi