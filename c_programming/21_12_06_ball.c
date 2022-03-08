#define T

#ifdef A
#include <stdio.h>
#include <string.h>

#define MAX_WIDTH 100
#define MAX_HEIGHT 50
enum result {loop, win, ok};

char field[MAX_HEIGHT][MAX_WIDTH + 1] = {0};
int step[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

typedef struct ball_ { int x; int y; int v; int prizes; } Ball;

int move(Ball *b, int n, int m) {
    b->x += step[b->v][0], b->y += step[b->v][1];
    switch (field[b->y][b->x]) {
        case '#':  return loop;
        case '/':  b->v += b->v % 2 ? 3 : 1; break;
        case '\\': b->v += b->v % 2 ? 1 : 3; break;
        case '*':  ++b->prizes; field[b->y][b->x] = ' '; break;
    }
    b->v %= 4;
    if (b->x == m - 2 && b->y == n - 2) return win;
    return ok;
}

int main() {
    FILE *in = fopen("input.txt", "rt"), *out = fopen("output.txt", "wt");
    fgets(field[0], MAX_WIDTH, in);
    int m = (int) strlen(field[0]) - 1, n, prizes = 0;
    for (n = 1; fgets(field[n], MAX_WIDTH, in); ++n)
        for (int i = 0; i < m; ++i) if (field[n][i] == '*') ++prizes;

    Ball ball = {1, 1, 0, 0};
    int result;
    while ((result = move(&ball, n, m)) == ok);
    fprintf(out, "%s", result == win ? (ball.prizes == prizes ? "yes\nyes\n" : "yes\nno\n") : "no\n");
    fclose(in), fclose(out);
}
#endif
