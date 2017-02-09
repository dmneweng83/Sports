#include <stdio.h>
#include <stdint.h>
#include <cstdlib>
#include <string.h>
#include <errno.h>

struct Player {
    char name[30];
    int cost;
    float score;
    char id[20];
    char team[5];
    char opponent[5];
};

struct PlayerSize {
    char name[10];
    int players;
    char file[20];
};


bool loadFile(const char* fileName, struct Player players[], int playersCount)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file: %s: %s\n", fileName, strerror(errno));
        return false;
    }
    int line = 0;
    while (!feof(file)) {
        if (fscanf(file, "%s %d %f %s %s %s", (players[line].name), &(players[line].cost), &(players[line].score), (players[line].id), (players[line].team), (players[line].opponent)) != 6)
            break;
        if (players[line].cost < 10) {
            fprintf(stderr, "%s:[%d] %s cost \"%d\" < 0\n", fileName, line, players[line].name,  players[line].cost);
            exit(1);
        }
        if (players[line].score < 0) {
           fprintf(stderr, "%s:[%d] score \"%f\" < 0\n", fileName, line, players[line].score);
            exit(1);
        }
        ++line;

        if (playersCount < line) {
            fprintf(stderr, "%s: There are more lines \"%d\" than playerCount \"%d\"\n", fileName, line, playersCount);
            return false;
        }
    }
    fclose(file);
    return true;
}

bool getPlayers(const char* fileName, struct PlayerSize positions[], int positionsCount)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file: %s: %s\n", fileName, strerror(errno));
        return false;
    }
    int line = 0;
    while (!feof(file)) {
        if (fscanf(file, "%s %d %s", (positions[line].name), &(positions[line].players), (positions[line].file)) != 3)
            break;
        ++line;
    }
    fclose(file);
    return true;
}

int main() {
    float bestscore = 0;
    int cheapgoalie, cheapdefense, cheapdefense2, cheapwing4 = 0;
    struct PlayerSize totalplayers[4];
    getPlayers("numplayers.txt", totalplayers, 4);

    int centers, wings, defenses, goalies = 0;
    if (strcmp(totalplayers[0].name, "center") == 0)
        centers = totalplayers[0].players;
    if (strcmp(totalplayers[1].name, "wing") == 0)
        wings = totalplayers[1].players;
    if (strcmp(totalplayers[2].name, "defense") == 0)
        defenses = totalplayers[2].players;
    if (strcmp(totalplayers[3].name, "goalie") == 0)
        goalies = totalplayers[3].players;

    struct Player center_players[centers];
    loadFile("center.txt", center_players, centers);
    struct Player wing_players[wings];
    loadFile("wing.txt", wing_players, wings);
    struct Player defense_players[defenses];
    loadFile("defense.txt", defense_players, defenses);
    struct Player goalie_players[goalies];
    loadFile("goalie.txt", goalie_players, goalies);
    int percent;
    int numerator = 0;
    int combination = (centers*(centers-1)*(wings-3)/2);

    FILE *fp = fopen("best.txt", "w+");
    FILE *csv = fopen("lineups.txt", "w+");
    
    cheapgoalie = goalie_players[goalies].cost;
    cheapdefense2 = defense_players[defenses].cost;
    cheapdefense = defense_players[defenses-1].cost;
    cheapwing4 = wing_players[wings].cost;
    float bestScore = 0;
    int count = 0;
    float bestgoalie, bestdefense, bestdefense2, bestwing = 0;

    for (int x = 0; x < goalies; ++x)
    {
        if (goalie_players[x].score > bestgoalie)
            bestgoalie = goalie_players[x].score;
    }

    for (int x = 0; x < defenses; ++x)
    {

        if ((defense_players[x].score < bestdefense) && (defense_players[x].score > bestdefense2))
        {
            bestdefense2 = defense_players[x].score;
        }

        else if (defense_players[x].score > bestdefense)
        {
            bestdefense2 = bestdefense;
            bestdefense = defense_players[x].score;
        }

    }

    for (int x = 0; x < wings; ++x)
    {
        if (wing_players[x].score > bestwing)
            bestwing = wing_players[x].score;
    }



    for (int center = 0; center < centers-1; ++center)
    {
        int centercost = center_players[center].cost;
        float centerscore = center_players[center].score;
        for (int center2 = center+1; center2 < centers; ++center2)
        {
            int center2cost = center_players[center2].cost;
            float center2score = center_players[center2].score;
            for (int wing = 0; wing < wings-3; ++wing)
            {
                ++numerator;
                percent=((numerator*100)/combination);
                printf ("%d out of %d is %d Complete!\n", numerator, combination, percent); 
                int wingcost = wing_players[wing].cost;
                float wingscore = wing_players[wing].score;

                for (int wing2 = wing+1; wing2 < wings-2 ; ++wing2)
                {
                    int wing2cost = wing_players[wing2].cost;
                    float wing2score = wing_players[wing2].score;
                    
                    for (int wing3 = wing2+1; wing3 < wings-1; ++wing3)
                    {
                        int wing3cost = wing_players[wing3].cost;
                        float wing3score = wing_players[wing3].score;

                        if (centercost + center2cost + wingcost + wing2cost + wing3cost + cheapwing4 + cheapdefense + cheapdefense2 + cheapgoalie > 55000)
                            continue;

                            if (centerscore + center2score + wingscore + wing2score + wing3score + bestwing + bestdefense2 + bestdefense + bestgoalie < (bestscore - 1.5))
                                continue;

                        for (int wing4 = wing3 + 1; wing4 < wings; ++wing4)
                        {
                            int wing4cost = wing_players[wing4].cost;
                            float wing4score = wing_players[wing4].score;

                            if (centercost + center2cost + wingcost + wing2cost + wing3cost + wing4cost + cheapdefense + cheapdefense2 + cheapgoalie > 55000)
                                continue;
                                if (centerscore + center2score + wingscore + wing2score + wing3score + wing4score + bestdefense2 + bestdefense + bestgoalie < (bestscore - 1.5))
                                    continue;

                            for (int defense = 0; defense < defenses-1; ++defense)
                            {
                                int defensecost = defense_players[defense].cost;
                                float defensescore = defense_players[defense].score;

                                if (centercost + center2cost + wingcost + wing2cost + wing3cost + wing4cost + defensecost + cheapdefense2 + cheapgoalie > 55000)
                                    continue;

                                    if (centerscore + center2score + wingscore + wing2score + wing3score + wing4score + defensescore + bestdefense + bestgoalie < (bestscore - 1.5))
                                        continue;

                                for (int defense2 = defense + 1; defense2 < defenses; ++defense2)
                                {
                                    int defense2cost = defense_players[defense2].cost;
                                    float defense2score = defense_players[defense2].score;

                                    if (centercost + center2cost + wingcost + wing2cost + wing3cost + wing4cost + defensecost + defense2cost + cheapgoalie > 55000)  
                                        continue;
                                  
                                    if (centerscore + center2score + wingscore + wing2score + wing3score + wing4score + defensescore + defense2score + bestgoalie < (bestscore - 1.5))
                                        continue;


                                    for (int goalie = 0; goalie < goalies; ++goalie)
                                    {
                                        int goaliecost = goalie_players[goalie].cost;

                                        int cost = centercost + center2cost + wingcost + wing2cost + wing3cost + wing4cost + defensecost + defense2cost + goaliecost;

                                        if (cost > 55000)
                                            continue;
                                        float score = center_players[center].score + center_players[center2].score + wing_players[wing].score + wing_players[wing2].score + wing_players[wing3].score + wing_players[wing4].score + defense_players[defense].score + defense_players[defense2].score + goalie_players[goalie].score;

                                        if (score > bestscore)
                                             bestscore = score;
                                        if (score > (bestscore - 1.5)) {

                                            if ((
                                            (center_players[center].team == center_players[center2].team) + 
                                            (center_players[center].team == wing_players[wing].team) +
                                            (center_players[center].team == wing_players[wing2].team) +
                                            (center_players[center].team == wing_players[wing3].team) +
                                            (center_players[center].team == wing_players[wing4].team) +
                                            (center_players[center].team == defense_players[defense].team) +
                                            (center_players[center].team == defense_players[defense2].team) +
                                            (center_players[center].team == goalie_players[goalie].team)) > 4)
                                                continue;

                                            if ((
                                            (center_players[center2].team == wing_players[wing].team) +
                                            (center_players[center2].team == wing_players[wing2].team) +
                                            (center_players[center2].team == wing_players[wing3].team) +
                                            (center_players[center2].team == wing_players[wing4].team) +
                                            (center_players[center2].team == defense_players[defense].team) +
                                            (center_players[center2].team == defense_players[defense2].team) +
                                            (center_players[center2].team == goalie_players[goalie].team)) > 4)
                                                continue;
                                            
                                            if ((
                                            (wing_players[wing].team == wing_players[wing2].team) +
                                            (wing_players[wing].team == wing_players[wing3].team) +
                                            (wing_players[wing].team == wing_players[wing4].team) +
                                            (wing_players[wing].team == defense_players[defense].team) +
                                            (wing_players[wing].team == defense_players[defense2].team) +
                                            (wing_players[wing].team == goalie_players[goalie].team)) > 4)
                                                continue;

                                            if ((
                                            (wing_players[wing2].team == wing_players[wing3].team) +
                                            (wing_players[wing2].team == wing_players[wing4].team) +
                                            (wing_players[wing2].team == defense_players[defense].team) +
                                            (wing_players[wing2].team == defense_players[defense2].team) +
                                            (wing_players[wing2].team == goalie_players[goalie].team)) > 4)
                                                continue;

                                            if ((
                                            (wing_players[wing3].team == wing_players[wing4].team) +
                                            (wing_players[wing3].team == defense_players[defense].team) +
                                            (wing_players[wing3].team == defense_players[defense2].team) +
                                            (wing_players[wing3].team == goalie_players[goalie].team)) > 4)
                                                continue;

                                            if ((
                                            (goalie_players[goalie].opponent == center_players[center2].team) +
                                            (goalie_players[goalie].opponent == wing_players[wing].team) +
                                            (goalie_players[goalie].opponent == wing_players[wing2].team) +
                                            (goalie_players[goalie].opponent == wing_players[wing3].team) +
                                            (goalie_players[goalie].opponent == wing_players[wing4].team) +
                                            (goalie_players[goalie].opponent == defense_players[defense].team) +
                                            (goalie_players[goalie].opponent == defense_players[defense2].team) +
                                            (goalie_players[goalie].opponent == center_players[center].team)) > 1) 
                                                continue;


                                            fprintf(csv, "%s %s %s %s %s %s %s %s %s %f\n",
                                                   center_players[center].id,
                                                   center_players[center2].id,
                                                   wing_players[wing].id,
                                                   wing_players[wing2].id,
                                                   wing_players[wing3].id,
                                                   wing_players[wing4].id,
                                                   defense_players[defense].id,
                                                   defense_players[defense2].id,
                                                   goalie_players[goalie].id,
                                                   score
                                                   );

                                            fprintf(fp, "Score: %f Cost: %d   Team: %s %s %s %s %s %s %s %s %s\n",
                                                   score, cost,
                                                   center_players[center].name,
                                                   center_players[center2].name,
                                                   wing_players[wing].name,
                                                   wing_players[wing2].name,
                                                   wing_players[wing3].name,
                                                   wing_players[wing4].name,
                                                   defense_players[defense].name,
                                                   defense_players[defense2].name,
                                                   goalie_players[goalie].name
                                                   );
                                            ++count;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(fp);
    fclose(csv);
}
