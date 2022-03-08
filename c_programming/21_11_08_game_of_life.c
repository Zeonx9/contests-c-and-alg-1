#define T

#ifdef T1
#include <stdio.h>

int n, m;

int neighbors(int i, int j, int universe[n][m]) {
    int moveY[] = {-1, -1, -1, 0, 0, 1, 1, 1},
        moveX[] = {-1, 0, 1, -1, 1, -1, 0, 1},
        count = 0;
    for (int k = 0; k < 8; ++k)
        count += universe[(i + moveY[k] + n) % n][(j + moveX[k] + m) % m];
    return count;
}

int nextGeneration(int universe[n][m], int tmp[n][m], int * counter){
    *counter = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j){
            int count = neighbors(i, j, universe);
            if (count == 3 || (universe[i][j] && count == 2)) {
                tmp[i][j] = 1;
                ++(*counter);
            } else
                tmp[i][j] = 0;
        }
    int changed = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (universe[i][j] != tmp[i][j])
                changed = 1;
            universe[i][j] = tmp[i][j], tmp[i][j] = 0;
        }
    return changed;
}

void print(int universe[n][m]){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            printf("%c", universe[i][j] ? 'x' : ' ');
        printf("\n");
    }
}

int main() {
    scanf("%d%d", &n, &m); // NOLINT(cert-err34-c)
    int universe[n][m];
    int universe_t[n][m];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", universe[i] + j); // NOLINT(cert-err34-c)

    int step = 1, alives = 0;
    for (int k = 1; k < 1001; ++k) {
        int changes = nextGeneration(universe, universe_t, &alives);
        if (k == step) {
            printf("Step %d: alives %d\n", step, alives);
            print(universe);
            step *= step < 1000 ? 10 : 1;
        }
        if (!changes || !alives) {
            step = k;
            break;
        }
    }
    printf("End life step %d\n", step);
}
#endif