#!/bin/bash

echo >> allplayers.csv

sed 's/"//g' allplayers.csv > allplayers3.csv
tr -d ' ' < allplayers3.csv > allplayers4.csv
tac allplayers4.csv > allplayers2.csv

rm allplayers3.csv
rm allplayers4.csv

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

rm goalie2.txt
touch goalie2.txt

rm wing2.txt
touch wing2.txt

rm defense2.txt
touch wing2.txt

rm center2.txt
touch center2.txt

goalie1=0
goalie2=0
wing1=0
wing2=0
wing3=0
wing4=0
wing5=0
defense1=0
defense2=0
defense3=0
center1=0
center2=0
center3=0


INPUT=allplayers2.csv
OLDIFS=$IFS
IFS=,
[ ! -f $INPUT ] && { echo "$INPUT file not found"; exit 99; }
while read id position first nick last project played salary game team opponent injury type
do

if [ "$injury" == "" ]; then



    FOUND=`fgrep -c "$team" "spread.txt"`
    if [[ $FOUND -eq 1 ]]; then
 
    spread=$(cat spread.txt | grep $team | awk '{print $2}')
    
    adjustment2=$(( ($spread*100)/($spread+100) ))
    adjustment2=$((($adjustment2%50)+100))
    adjustment=$( echo "scale=2;$adjustment2/100" | bc -l )
   
#    echo "$team $spread $project $adjustment"
    project=$( echo "$project*$adjustment" | bc -l )
#    echo "$team $spread $project $adjustment"

    fi



     if (( $(echo "$project 7.5" | awk '{print ($1 > $2)}') )); then
     if (( $(echo "$project 9.5" | awk '{print ($1 < $2)}') && $(echo "$salary 5000" | awk '{print ($1 > $2)}')  )); then
          continue
     fi


          if [ "$position" == "G" ]; then
               if (( $(echo "$project 15" | awk '{print ($1 < $2)}') )); then
                  continue
               fi

               if (( $(echo "$project $goalie2" | awk '{print ($1 > $2)}') )); then

                   echo "$last$first $salary $project $id $team $opponent" >> goalie2.txt
                   goalie2=$project
                   if (( $(echo "$project $goalie1" | awk '{print ($1 > $2)}') )); then
                       goalie2=$goalie1
                       goalie1=$project
                   fi
               fi

          fi

          if [ "$position" == "W" ]; then

               if (( $(echo "$project $wing5" | awk '{print ($1 > $2)}') )); then

                   echo "$last$first $salary $project $id $team $opponent" >> wing2.txt
                   wing5=$project
                   if (( $(echo "$project $wing4" | awk '{print ($1 > $2)}') )); then
                       wing5=$wing4
                       wing4=$project
                   fi
                   if (( $(echo "$project $wing3" | awk '{print ($1 > $2)}') )); then
                       wing4=$wing3
                       wing3=$project
                   fi
                   if (( $(echo "$project $wing2" | awk '{print ($1 > $2)}') )); then
                       wing3=$wing2
                       wing2=$project
                   fi
                   if (( $(echo "$project $wing1" | awk '{print ($1 > $2)}') )); then
                       wing2=$wing1
                       wing1=$project
                   fi
               fi



          fi

          if [ "$position" == "D" ]; then


              if (( $(echo "$project $defense3" | awk '{print ($1 > $2)}') )); then

                   echo "$last$first $salary $project $id $team $opponent" >> defense2.txt
                   defense3=$project
                   if (( $(echo "$project $defense2" | awk '{print ($1 > $2)}') )); then
                       defense3=$defense2
                       defense2=$project
                   fi
                   if (( $(echo "$project $defense1" | awk '{print ($1 > $2)}') )); then
                       defense2=$defense1
                       defense1=$project
                   fi
               fi




          fi

          if [ "$position" == "C" ]; then

              if (( $(echo "$project $center3" | awk '{print ($1 > $2)}') )); then

                   echo "$last$first $salary $project $id $team $opponent" >> center2.txt
                   center3=$project
                   if (( $(echo "$project $center2" | awk '{print ($1 > $2)}') )); then
                       center3=$center2
                       center2=$project
                   fi
                   if (( $(echo "$project $center1" | awk '{print ($1 > $2)}') )); then
                       center2=$center1
                       center1=$project
                   fi
               fi




          fi
     fi
fi
 
done < $INPUT
IFS=$OLDIFS

tac goalie2.txt > goalie.txt
tac wing2.txt > wing.txt
tac center2.txt > center.txt
tac defense2.txt > defense.txt

rm goalie2.txt
rm wing2.txt
rm center2.txt
rm defense2.txt

WC=`wc -l center.txt`
echo "center $WC" >> numplayers.txt

WC=`wc -l wing.txt`
echo "wing $WC" >> numplayers.txt

WC=`wc -l defense.txt`
echo "defense $WC" >> numplayers.txt

WC=`wc -l goalie.txt`
echo "goalie $WC" >> numplayers.txt



