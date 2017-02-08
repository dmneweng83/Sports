#!/bin/bash

echo >> allplayers.csv

sed 's/"//g' allplayers.csv > allplayers3.csv
tr -d ' ' < allplayers3.csv > allplayers2.csv

rm allplayers3.csv

rm best.txt
touch best.txt

rm goalie.txt
touch goalie.txt

rm center.txt
touch center.txt

rm wing.txt
touch wing.txt

rm defense.txt
touch defense.txt

rm numplayers.txt
touch numplayers.txt

INPUT=allplayers2.csv
OLDIFS=$IFS
IFS=,
[ ! -f $INPUT ] && { echo "$INPUT file not found"; exit 99; }
while read id position first nick last project played salary game team opponent injury type
do
 
if [ "$injury" == "" ]; then

     if [ "$position" == "G" ]; then
          echo "$last$first $salary $project $id $team $opponent" >> goalie.txt
     fi

     if [ "$position" == "W" ]; then
          echo "$last$first $salary $project $id $team $opponent" >> wing.txt
     fi

     if [ "$position" == "D" ]; then
          echo "$last$first $salary $project $id $team $opponent" >> defense.txt
     fi

     if [ "$position" == "C" ]; then
          echo "$last$first $salary $project $id $team $opponent" >> center.txt
     fi



fi
 
done < $INPUT
IFS=$OLDIFS

WC=`wc -l center.txt`
echo "center $WC" >> numplayers.txt

WC=`wc -l wing.txt`
echo "wing $WC" >> numplayers.txt

WC=`wc -l defense.txt`
echo "defense $WC" >> numplayers.txt

WC=`wc -l goalie.txt`
echo "goalie $WC" >> numplayers.txt


