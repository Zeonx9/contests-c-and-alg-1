#define ACTIVE_
#ifdef ACTIVE

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r;
    int c;
    char letter;
} Figure;

char board[8][8];
Figure king, queen, knight, paw;
int moveY[] = {-1, -1, -1, 0, 0, 1, 1, 1},
    moveX[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void scanPosition(Figure * figure){
    char input[3];
    scanf("%s", input);
    figure->r = input[1] - '1';
    figure->c = input[0] < 'I' ? input[0] - 'A' : input[0] - 'a';
}

void init(Figure **figures){
    char letters[] = {'k', 'q', 'n', 'p'};
    for (int i = 0; i < 4; ++i){
        scanPosition(figures[i]);
        figures[i]->letter = letters[i];
        board[figures[i]->r][figures[i]->c] = figures[i]->letter;
    }
}

int checkPosition(int r, int c) {
    if (r < 0 || r > 7 || c < 0 || c > 7 ||
        abs(r - queen.r) == abs(c - queen.c) || r - queen.r == 0 || c - queen.c == 0 ||
        abs(r - knight.r) == 1 && abs(c - knight.c) == 2 || abs(r - knight.r) == 2 && abs(c - knight.c) == 1 ||
        r == knight.r && c == knight.c || r - paw.r == 1 && abs(c - paw.c) == 1 || r == paw.r && c == paw.c)
            return 0;
    return 1;
}

int isCheck(){ return !checkPosition(king.r, king.c); }
int hasMoves() {
    for (int i = 0; i < 8; ++i)
        if (checkPosition(king.r + moveY[i], king.c + moveX[i]))
            return 1;
    return 0;
}

void print(){
    for (int i = 7; i >= 0; --i) {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; ++j) {
            char ch[3];
            switch (board[i][j]) {
                case 'k': { ch[0] = 'K', ch[1] = 'g'; break; }
                case 'q': { ch[0] = 'Q', ch[1] = 'n'; break; }
                case 'n': { ch[0] = 'N', ch[1] = 't'; break; }
                case 'p': { ch[0] = 'P', ch[1] = 'w'; break; }
                default : ch[0] = ch[1] = (i + j) % 2 ? -80 : -78;
            }
            printf("%s", ch);
        }
        printf("\n");
    }
    printf("   A B C D E F G H \n\n");
}

int main(){
    Figure *figures[] = {&king, &queen, &knight, &paw};
    init(figures);
    print();
    if (isCheck())
        printf("%s\n", hasMoves() ? "Check" : "Checkmate");
    else
        printf("%s\n", hasMoves() ? "Regular" : "Stalemate");
}
#endif