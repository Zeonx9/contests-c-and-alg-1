#define T3

#ifdef T1
#include <stdio.h>
#include <string.h>

#define NAME_LEN 20
#define MAX_TEAMS 10

typedef struct {
    char name[NAME_LEN + 1];
    int games; int home; int wins; int loses; int goals; int miss;
    int opponents[MAX_TEAMS];
} TeamInfo;

void clear(TeamInfo * t) {
    t->games = t->home = t->home = t->wins = t->loses = t->goals = t->goals = t->miss = 0;
    for (int i = 0; i < MAX_TEAMS; ++i)
        t->opponents[i] = 0;
}

int find(const char *s, TeamInfo *teams, int *len){
    for (int i = 0; i < *len; ++i)
        if (strcmp(s, teams[i].name) == 0)
            return i;

    strcpy(teams[(*len)++].name, s);
    clear(teams + *len - 1);
    return *len - 1;
}

void update(TeamInfo * teams, int id1, int id2, int g1, int g2) {
    ++teams[id1].games, ++teams[id2].games; ++teams[id1].home;
    if (g1 != g2) {
        int w = g1 > g2 ? id1 : id2;
        int l = g1 > g2 ? id2 : id1;
        ++teams[w].wins, ++teams[l].loses;
    }
    teams[id1].goals += g1, teams[id2].goals += g2;
    teams[id1].miss += g2, teams[id2].miss += g1;
    teams[id1].opponents[id2] = 1;
    teams[id2].opponents[id1] = 1;
}
int countOpponents(TeamInfo *team) {
    int r = 0;
    for (int i = 0; i < MAX_TEAMS; ++i)
        r += team->opponents[i];
    return r;
}

void printTeam(FILE * f, TeamInfo *t) {
    fprintf(f, "%s %d %d %d %d %d %d %d\n", t->name, t->games, t->home, t->wins, t->loses, t->goals, t->miss,
            countOpponents(t));
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    char team1[NAME_LEN + 1], team2[NAME_LEN + 1];
    int score1, score2, teamsCount = 0;
    TeamInfo teams[MAX_TEAMS];

    for (;fscanf(input, "%s - %s %d:%d", team1, team2, &score1, &score2) != EOF;) {
        int i = find(team1, teams, &teamsCount), j = find(team2, teams, &teamsCount);
        update(teams, i, j, score1, score2);
    }
    for (int i = 0; i < teamsCount; ++i) {
        printTeam(output, teams + i);
    }
}

#endif

#ifdef T2
#include <stdio.h>
#include <string.h>

#define NAME_LEN 20
#define MAX_TEAMS 10

typedef struct {
    char * name; int games; int away; int wins; int goals;
} Opponent;

typedef struct {
    char name[NAME_LEN + 1];
    int numberOfOpponents;
    Opponent opponents[MAX_TEAMS];
}Team;

void clear(Opponent *o) {
    o->games = o->away = o->wins = o->goals = 0;
}

int find(const char *s, Team *teams, int *len){
    for (int i = 0; i < *len; ++i)
        if (strcmp(s, teams[i].name) == 0)
            return i;

    strcpy(teams[(*len)++].name, s);
    teams[*len - 1].numberOfOpponents = 0;
    return *len - 1;
}

int findOpponent(char *s, Team *t) {
    for (int i = 0; i < t->numberOfOpponents; ++i){
        if (strcmp(s, t->opponents[i].name) == 0)
            return i;
    }
    t->opponents[t->numberOfOpponents++].name = s;
    clear(t->opponents + t->numberOfOpponents - 1);
    return t->numberOfOpponents - 1;
}

void updateOpponent(Opponent * o, int away, int win, int goals) {
    ++o->games;
    o->away += away;
    o->wins += win;
    o->goals += goals;
}

void update(Team * teams, int id1, int id2, int g1, int g2) {
    int i = findOpponent(teams[id2].name, teams + id1), j = findOpponent(teams[id1].name, teams + id2);
    updateOpponent(teams[id1].opponents + i, 0, g1 > g2, g1);
    updateOpponent(teams[id2].opponents + j, 1, g2 > g1, g2);
}

void printOpponent(FILE * f, Opponent *o) {
    fprintf(f, "%s %d %d %d %d\n", o->name, o->games, o->away, o->wins, o->goals);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    char team1[NAME_LEN + 1], team2[NAME_LEN + 1];
    int score1, score2, teamsCount = 0;
    Team teams[MAX_TEAMS];

    for (; fscanf(input, "%s - %s %d:%d", team1, team2, &score1, &score2) != EOF;) {
        int i = find(team1, teams, &teamsCount), j = find(team2, teams, &teamsCount);
        update(teams, i, j, score1, score2);
    }

    for (int i = 0; i < teamsCount; ++i) {
        fprintf(output, "%s\n", teams[i].name);
        for (int j = 0; j < teams[i].numberOfOpponents; ++j)
            printOpponent(output, teams[i].opponents + j);
    }
}
#endif


