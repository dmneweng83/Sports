#!/bin/bash


clear && echo -en "\e[3]"

while true; do
    echo "1 - Grab Original CSV from desktop"
    echo "2 - Init allplayers.csv"
    echo "3 - Run Main"
    echo "4 - Create csvs"
    echo "5 - "
    echo "6 - "
    echo "7 - "
    echo "8 - "
    echo "9 - Move CSV Lineup Folder back to desktop"
    echo "99 - exit"
    read -p "Pick an option:" choice
    case $choice in

        [1] ) clear
              `cp /mnt/c/Users/meyer/Desktop/Fanduel/Players/allplayers.csv allplayers.csv`
              echo "You moved lineups from desktop to folder"
              echo "Pick an option";;

        [2] ) clear
              `./init.sh`
              echo "allplayers.csv has been init"
              echo "Pick an option:";;

        [3] ) clear
              `./main`
              echo "Main Completed"
              `sort -k1n best.txt > best2.txt`
              `mv -f best2.txt best.txt`
              `rm best2.txt`
              `sort -k10nr lineups.txt > lineups2.txt`
              `mv -f lineups2.txt lineups.txt`
              `rm lineups2.txt`
              echo "Pick an option";;

        [4] ) clear
              `./makecsv.sh`
              echo "150 CSV files have been made"
              echo "Pick an option";;

        [5] ) clear
              echo "";;

        [6] ) clear
              echo "";;

        [7] ) clear
              echo "";;

        [8] ) clear
              echo "";;

        9 ) clear
              `cp -fr /lineups /mnt/c/Users/meyer/Desktop/Fanduel/lineups`
              echo "You moved lineups folder back to desktop"
              echo "Pick an option";;

        99 ) clear && exit;;

        * )  clear
             echo "Please make a selection!";;
    esac
done 
