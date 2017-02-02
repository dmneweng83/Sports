#include <stdio.h>
#include <stdint.h>
#include <cstdlib>
#include <string.h>
#include <errno.h>

struct player {
    char name[30];
    int cost;
    float score;
    char id[20];
    char team[5];
    char opponent[5];
};

struct playersize {
    char name[10];
    int players;
    char file[20];
};


bool loadFile(const char* fileName, struct player players[], int playersCount)
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
        if (players[line].cost < 0) {
            fprintf(stderr, "%s:[%d] cost < 0\n", fileName, line);
            exit(1);
        }
        if (players[line].score < 0) {
            fprintf(stderr, "%s:[%d] score < 0\n", fileName, line);
            exit(1);
        }
        ++line;
        if (playersCount <= line) {
            fprintf(stderr, "%s: There are more lines \"%d\" than playerCount \"%d\"\n", fileName, line, playersCount);
            return false;
        }
    }
    fclose(file);
    return true;
}

bool getPlayers(const char* fileName, struct playersize positions[], int positionsCount)
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
    struct playersize totalplayers[4];
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

    struct player center_players[centers];
    loadFile("center.txt", center_players, centers);
    struct player wing_players[wings];
    loadFile("wing.txt", wing_players, wings);
    struct player defense_players[defenses];
    loadFile("defense.txt", defense_players, defenses);
    struct player goalie_players[goalies];
    loadFile("goalie.txt", goalie_players, goalies);
    
    FILE *fp = fopen("best.txt", "w+");
    FILE *csv = fopen("lineups.txt", "w+");

    float bestScore = 0;
    int_fast64_t count = 0;
    for (int center = 0; center < centers-1; ++center)
    {
        int centercost = center_players[center].cost;
        for (int center2 = center+1; center2 < centers; ++center2)
        {
            int center2cost = center_players[center2].cost;
            for (int wing = 0; wing < wings-3; ++wing)
            {
                int wingcost = wing_players[wing].cost;
                for (int wing2 = wing+1; wing2 < wings-2 ; ++wing2)
                {
                    int wing2cost = wing_players[wing2].cost;
                    //if (qbcost + rb1cost + rb2cost + wr1cost > 37400)
                    //    cotinue;
                    for (int wing3 = wing2+1; wing3 < wings-1; ++wing3)
                    {
                        int wing3cost = wing_players[wing3].cost;
                        //if (qbcost + rb1cost + rb2cost + wr1cost + wr2cost > 42100)
                        //   continue;
                        for (int wing4 = wing3 + 1; wing4 < wings; ++wing4)
                        {
                            int wing4cost = wing_players[wing4].cost;
                            //if (qbcost + rb1cost + rb2cost + wr1cost + wr2cost + wr3cost > 46700)
                            //    continue;
                            for (int defense = 0; defense < defenses-1; ++defense)
                            {
                                int defensecost = defense_players[defense].cost;
                                //if (qbcost + rb1cost + rb2cost + wr1cost + wr2cost + wr3cost + tecost > 51500)
                                //    continue;
                                for (int defense2 = defense+1; defense2 < defenses; ++defense2)
                                {
                                    int defense2cost = defense_players[defense2].cost;
                                    //if (qbcost + rb1cost + rb2cost + wr1cost + wr2cost + wr3cost + tecost + kcost > 56000)
                                    //    continue;
                                    for (int goalie = 0; goalie < goalies; ++goalie)
                                    {
                                        int goaliecost = goalie_players[goalie].cost;

                                        int cost = centercost + center2cost + wingcost + wing2cost + wing3cost + wing4cost + defensecost + defense2cost + goaliecost;
                                        if (cost > 55000)
                                            continue;
                                        
                                        float score = center_players[center].score + center_players[center2].score + wing_players[wing].score + wing_players[wing2].score + wing_players[wing3].score + wing_players[wing4].score + defense_players[defense].score + defense_players[defense2].score + goalie_players[goalie].score;
                                        ++count;
                                        if (score > 100) {


                                            fprintf(csv, "%s %s %s %s %s %s %s %s %s %f",
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

                                            fprintf(fp, "Score: %f Cost: %d   Team: %s %s %s %s %s %s %s %s %s",
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
                                            bestScore = score;
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
