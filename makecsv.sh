#!/bin/bash

x=0
echo "C,C,W,W,W,W,D,D,G" > lineups/lineup_$x.csv

INPUT="lineups.txt"
[ ! -f $INPUT ] && { echo "$INPUT file not found"; exit 99; }

while read c1 c2 w1 w2 w3 w4 d1 d2 g1 score
do
echo "$c1"
     y=$((x))
     x=$((x+1))
     cp lineups/lineup_$y.csv lineups/lineup_$x.csv
     echo "$c1,$c2,$w1,$w2,$w3,$w4,$d1,$d2,$g1" >> lineups/lineup_$x.csv
     if (("$x" >= "150")); then
        break 
     fi
done < $INPUT
