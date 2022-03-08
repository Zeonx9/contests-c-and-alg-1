#define ACTIVE_
#ifdef ACTIVE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int field[10][10] = {};
int checked[100] = {};

int check(int i, int j, int len, int vertical) {
    if (!vertical && j + len > 9 || vertical && i + len > 9)
        return 0;
    int x1 = j? j - 1 : j, x2 = + j < 9 ? j + 1 : j,
        y1 = i? i - 1 : i, y2 = + i < 9 ? i + 1 : i;
    if (vertical) y2 += len - 1; else x2 += len - 1;

    for (int a = y1; a <= y2; ++a)
        for (int b = x1; b <= x2; ++b) {
            checked[a * 10 + b] = 1;
            if (field[a][b])
                return 0;
        }
    return 1;
}

void findPosition(int *i, int *j, int *align, int len, int *tempCheck){
    while (checked[*i * 10 + *j] || tempCheck[*i * 10 + *j])
        *i = rand() % 10, *j = rand() % 10, *align = rand() % 2; // NOLINT(cert-msc50-cpp)

    if (!check(*i, *j, len, *align)) {
        tempCheck[*i * 10 + *j] = 1;
        findPosition(i, j, align, len, tempCheck);
    }
}

void setShip(int i, int j, int len, int vertical){
    int stopI = i + (vertical ? len : 1), stopJ = j + (vertical ? 1 : len);
    for (int a = i; a < stopI; ++a)
        for (int b = j; b < stopJ; ++b)
            field[a][b] = 1;
}

void fill() {
    for (int len = 4; len > 0; --len) {
        int tempCheck[100] = {};
        for (int k = 5 - len; k > 0; --k) {
            int i = rand() % 10, j = rand() % 10, align = rand() % 2; // NOLINT(cert-msc50-cpp)
            findPosition(&i, &j, &align, len, tempCheck);
            setShip(i, j, len, align);
        }
    }
}

void print(){
    printf("    A B C D E F G H I J\n");
    for (int i = 0; i < 10; ++i) {
        printf("%2d ", i + 1);
        for (int j = 0; j < 10; ++j)
            for (int k = 0; k < 2; ++k)
                printf("%c", field[i][j] ? 178 : 176);
        printf("\n");
    }
}

int main() {
    srand(time(0)); // NOLINT(cert-msc51-cpp)
    fill();
    print();
}
#endif