#define T

#ifdef T52
#include <stdio.h>
#include <string.h>

#define SIZE 20
#define TEAM_NUMBER 10

typedef struct teamInfo_ {
    char name[SIZE + 1];
    int wins;
    int score;
    int points;
} TeamInfo;

int find(const char *s, TeamInfo *teams, int len){
    for (int i = 0; i < len; ++i)
        if (strcmp(s, teams[i].name) == 0)
            return i;
    return -1;
}

int main () {
    FILE *in = fopen("input.txt", "rt"), *out = fopen("output.txt", "wt");

    TeamInfo teams[TEAM_NUMBER];

    char team1[SIZE + 1], team2[SIZE + 1];
    int g1, g2, size = 0, champion = -1;
    while (fscanf(in, "%s - %s %d:%d", team1, team2, &g1, &g2) != EOF) {
        int i = find(team1, teams, size), j = find(team2, teams, size);
        if (i < 0) { i = size; strcpy(teams[size++].name, team1); }
        if (j < 0) { j = size; strcpy(teams[size++].name, team2); }

        int winner = g1 > g2 ? i : g1 < g2 ? j : -1;
        if (winner < 0)
            ++teams[i].points, ++teams[j].points;
        else {
            ++teams[winner].wins;
            teams[winner].points += 3;
            teams[i].score += g1 - g2;
            teams[j].score += g2 - g1;
        }
        if (champion < 0 || teams[winner].wins > teams[champion].wins ||
            teams[champion].wins == teams[winner].wins && teams[winner].score > teams[champion].score)
            champion = winner;
    }

    for (int i = 0; i < size; ++i) {
        if (teams[i].wins == teams[champion].wins && teams[champion].score == teams[i].score)
            fprintf(out, "%s %d %d\n", teams[i].name, teams[i].points, teams[i].score);
    }
    fclose(in), fclose(out);
}
#endif

#ifdef T5
#include <stdio.h>
#include <string.h>

#define SIZE 20
#define TEAM_NUMBER 10

int find(const char *s, char ss[][SIZE + 1], int len){
    for (int i = 0; i < len; ++i)
        if (strcmp(s, ss[i]) == 0)
            return i;
    return -1;
}

int main () {
    FILE *in = fopen("input.txt", "rt"),
        *out = fopen("output.txt", "wt");

    char teams[TEAM_NUMBER][SIZE + 1];
    int points[TEAM_NUMBER] = {0}, matches[TEAM_NUMBER] = {0}, scores[TEAM_NUMBER] = {0},
        champion = -1;

    char team1[SIZE + 1], team2[SIZE + 1];
    int g1, g2, size = 0;
    while (fscanf(in, "%s - %s %d:%d", team1, team2, &g1, &g2) != EOF) {
        int i = find(team1, teams, size), j = find(team2, teams, size);
        if (i < 0) { i = size; strcpy(teams[size++], team1); }
        if (j < 0) { j = size; strcpy(teams[size++], team2); }

        int winner = g1 > g2 ? i : g1 < g2 ? j : -1;
        if (winner < 0)
            ++points[i], ++points[j];
        else {
            ++matches[winner];
            points[winner] += 3;
            scores[i] += g1 - g2;
            scores[j] += g2 - g1;
        }
        if (champion < 0 || matches[winner] > matches[champion] ||
            matches[champion] == matches[winner] && scores[winner] > scores[champion])
            champion = winner;
    }

    for (int i = 0; i < TEAM_NUMBER; ++i) {
        if (matches[i] == matches[champion] && scores[champion] == scores[i])
            fprintf(out, "%s %d %d\n", teams[i], points[i], scores[i]);
    }
    fclose(in), fclose(out);
}
#endif

#ifdef T4
#endif

#ifdef T3
#include <stdio.h>

int main () {
    FILE *in = fopen("input.txt", "rt"),
            *out = fopen("output.txt", "wt");

    int count = 0;
    char ch;
    while ((ch = (char) getc(in)) != EOF) {
        if ('0' <= ch && ch <= '9')
            ++count;
    }
    fprintf(out, "%d", count);
    fclose(in), fclose(out);
}
#endif

#ifdef T2
#include <stdio.h>
#include <string.h>

#define SIZE 10000
void fputsReverse(char * str, FILE * dst) {
    int len = (int) strlen(str);
    for (int i = len - 1; i > -1; --i){
        putc(str[i], dst);
    }
}

void reverse(FILE *src, FILE *dst) {
    char s[SIZE + 1];
    if ((fgets(s, SIZE, src)) != NULL) {
        reverse(src, dst);
        fputsReverse(s, dst);
    }
}

int main () {
    FILE *in = fopen("input.txt", "rt"),
        *out = fopen("output.txt", "wt");

    reverse(in, out);
    fclose(in), fclose(out);
}
#endif

#ifdef T1
#include <stdio.h>
#define SIZE 10000

void reverse(FILE *src, FILE *dst) {
    char s[SIZE + 1];
    if (!fgets(s, SIZE, src)) return;
    reverse(src, dst);
    fputs(s, dst);
}

int main () {
    FILE *in = fopen("input.txt", "rt"),
        *out = fopen("output.txt", "wt");

    reverse(in, out);
    fclose(in), fclose(out);
}
#endif
