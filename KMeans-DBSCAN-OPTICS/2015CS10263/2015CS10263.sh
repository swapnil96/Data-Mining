#!/bin/sh

km="-kmeans"
db="-dbscan"
op="-optics"
ck="-check"

if [ "$2" == "$pl" ]
then
    rm logs.txt
    for x in {1,5,10,25,50,90}
    do
        echo $x
        echo -n "$(./apriori $1 $x temp 1)" >> logs.txt 
        echo -n " " >> logs.txt
        echo -n "$(./fptree $1 $x temp 1)" >> logs.txt
        echo "" >> logs.txt 
    done
    python plot.py
elif [ "$2" == "$ck" ]
then
    for x in `seq 1 100`
    do
        echo $x
        ./apriori $1 $x t1 0
        ./fptree $1 $x t2 0
        python check.py t1.txt t2.txt >> ans.txt 
    done
else
    if [ "$3" == "$ap" ]
    then
        ./apriori $1 $2 $4 0
    elif [ "$3" == "$fp" ]
    then
        ./fptree $1 $2 $4 0
    fi
fi