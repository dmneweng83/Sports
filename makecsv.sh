#!/bin/bash

rm lineups/*
sort -k10n lineups.txt > lineups2.txt
rm lineups.txt
tac lineups2.txt > lineups.txt
rm lineups2.txt

x=0
echo "C,C,W,W,W,W,D,D,G" > lineups/lineup_$x.csv

INPUT="lineups.txt"
[ ! -f $INPUT ] && { echo "$INPUT file not found"; exit 99; }

while read c1 c2 w1 w2 w3 w4 d1 d2 g1 score
do
     y=$((x))
     x=$((x+1))
     cp lineups/lineup_$y.csv lineups/lineup_$x.csv
     echo "$c1,$c2,$w1,$w2,$w3,$w4,$d1,$d2,$g1" >> lineups/lineup_$x.csv
     if (("$x" >= "150")); then
        break 
     fi
done < $INPUT
