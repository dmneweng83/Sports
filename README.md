# Sports

Running the program from start to finish:

Get the csv with all players from the fanduel website
    - Click on a contest at a time frame
        - Click "Download Player List"
        - This list is usable for any contest for that time slot (ie. the 7pm main)
    - Make adjustments for what players to omit from master list
        - ie. player is not starting that game
        - A player usually not starting is, so adjust his initial projections
        - On the last column add what line each player is in. Can be found on fanduel

Populate the spread.txt
    - This is just a file with the Letter code of team, and their vegas odds
        - Example: Boston is a -220 (big favorite) would be written BOS 220
        - This is used to adjust players fantasy projections
            - The better a team is favored to do, the better boost players on that team get

Run init.sh
    - The script sets up the txt files with the players and the information needed
        - This script reads through the list of players &
            - Adjust the players projections
            - Only keeps players in the top lines of teams
            - Only keeps players that score enough to be considered
            - Does not keep players if there are enough players that score more and are cheaper
        - Then assigns the players to their correct txt file based on position
        - Creates a txt file summerizing the number of players per position

main.cpp
    - comiles to main
    - Code to generate all the possible lineups based on the positions generated
    - Now is updated so that at least two lines will have two players in it
    - Displays the % of the way through the posibilities it needs to compare
    - Will check to see if a lineup is cheap enough
    - Will see if a lineup is within 2 points of the current-best, if so will add that lineup to the posible lineups

makecsv.sh
    - Code needed to take the output of the best lineups, and put them into a csv form
    - It will create up to 150 csvs into a folder
        - Each csv will have the number of lineups according the the file name
            - ie. lineups_23.csv will contain 23 lineups

Upload to fanduel
    - Go back to the time slot on the webpage from where the csv originally came from
    - Choose the contest that you want to enter
        - ie. Thu NHL Breakaway ($30,000 Guaranteed)
    - From the player input screen, choose upload csv
        - Upload csv to the fanduel website based on how many lineups you want
            - If you want 25 lineups, then use that csv

****************

UPDATES NEEDED
    - A way to keep lineups so they dont have the same player in every lineup
        - Set a percentage, 90%, So lineups created will have at most a player only 90% of the time, else skip to next lineup

****************
For now main.sh is not usable
when running main from main.sh it completly slows the process down
as it is running a program from inside a program

Also it is imcomplete, and needs to be verified that it works
****************
main.sh  -  Is a step by step process to go from start to end
            first copies the list of players from my desktop
            then runs the init.sh
            then runs main
            then creates the csv
            then finally sends the folder of csvs back to desktop
