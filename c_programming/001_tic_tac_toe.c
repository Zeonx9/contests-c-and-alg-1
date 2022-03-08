#define ACTIVE
#ifdef ACTIVE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char field[3][3] = {};
int left = 9;

int  set(int i, int j, char c) {
    if (!field[i][j]){
        field[i][j] = c;
        --left;
        return 1;
    }
    return  0;
}

void getFromUser(char c) {
    int i, j;
    printf("Your turn, input position (number of 1 <= row <= 3 then number of 1 <= column <= 3):\n");
    scanf("%d %d", &i, &j); // NOLINT(cert-err34-c)
    if (i < 0 || i > 3 || j < 0 || j > 3 || !set(i - 1, j - 1, c)){
        printf("This cell is set already, try another position\n");
        getFromUser(c);
    }
}

void getFromComputer(char c) {
    int index = rand() % 9; // NOLINT(cert-msc50-cpp)
    if(!set(index / 3, index % 3, c))
        getFromComputer(c);
    else
        printf("Computer's turn\n");
}

int  check(){
    for (int i = 0; i < 3; ++i){
        if (field [i][0] != 0 && field[i][0] == field[i][1] && field[i][1] == field[i][2] ||
            field [0][i] != 0 && field[0][i] == field[1][i] && field[1][i] == field[2][i])
            return 1;
    }
    if (field [0][0] != 0 && field[0][0] == field[1][1] && field[1][1] == field[2][2] ||
        field [2][0] != 0 && field[0][2] == field[1][1] && field[1][1] == field[2][0])
        return 1;
    return 0;
}

void clear(){
    for (int i = 0; i < 9; ++i)
        field[i / 3][i % 3] = 0;
    left = 9;
}

void print(){
    for (int i = 0; i < 3; ++i) {
        printf("|");
        for (int j = 0; j < 3; ++j)
            printf("%2c", field[i][j] ? field[i][j] : '-');
        printf(" |\n");
    }
}

void play(void (*first)(char)){
    char win[] = "You won! Congrats!\n",
        loose[] = "You loose( Try again\n";
    void (*second)(char) = first == &getFromUser ? &getFromComputer : &getFromUser;
    while (left){
        first('x');
        print();
        if (check()){
            printf("%s", first == &getFromUser ? win : loose);
            return;
        }
        if(!left)
            break;
        second('0');
        print();
        if (check()){
            printf("%s", first == &getFromUser ? loose : win);
            return;
        }
    }
    printf("It's draw. Friendship won!\n");
}

int main() {
    int again = 1;
    char ch;
    srand(time(0)); // NOLINT(cert-msc51-cpp)
    while (again == 1){
        printf("Game has started!\nDo you prefer \'x\' or \'0\'? enter \'x\'"
               " to play as it, by default you playing for \'0\':\n");
        scanf(" %c", &ch);
        if (ch == 'x')
            play(&getFromUser);
        else
            play(&getFromComputer);
        printf("\nWanna play again? - Enter 1! If you think it's enough for you - enter any number besides 1:\n");
        scanf("%d", &again);// NOLINT(cert-err34-c)
        clear();
    }
    return 0;
}
#endif