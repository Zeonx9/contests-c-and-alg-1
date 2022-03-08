#define T
 
#ifdef T5
#include <stdio.h>

#define MAX_LEN 100000
#define N 62

int getIndex(char c) {
    int n = -1;
    if ('A' <= c && c <= 'Z')
        n = c - 'A';
    else if ('a' <= c && c <= 'z')
        n = c + 26 -  'a';
    else if ('0' <= c && c <= '9')
        n = c + 52 - '0';
    return n;
}
char getChar(int i) {
    if (i < 26)
        return (char ) ('A' + i);
    if (i < 52)
        return  (char ) ('a' + i - 26);
    return (char ) ('0' + i - 52);
}

int main() {
    char s[MAX_LEN + 1];
    int  chars[N] = { 0 }, word[N] = { 0 };
    fgets(s, MAX_LEN, stdin);
    int i = -1, count = 0;

    while (s[++i]) {
        if (s[i] == ' ' || s[i] == '\n')
            continue;

        ++count;
        int j = i - 1;
        while (s[++j] && s[j] != ' ' && s[j] != '\n') {
            int ind = getIndex(s[j]);
            ++word[ind];
            if (word[ind] == 1)
                ++chars[getIndex(s[j])];
        }
        for (int k = 0; k < N; ++k)
            word[k] = 0;
        i = j - 1;
    }

    int countUnique = 0, countUniversal = 0;
    printf("Universal: ");
    for (i = 0; i < N; ++i) {
        if (chars[i] == count) {
            ++countUniversal;
            printf("%c ", getChar(i));
        }
    }
    printf("%s\n", countUniversal ? "" : "no");
    printf("Unique: ");
    for (i = 0; i < N; ++i) {
        if (chars[i] == 1) {
            ++countUnique;
            printf("%c ", getChar(i));
        }
    }
    printf("%s\n", countUnique ? "" : "no");
}
#endif

#ifdef T4
#include <stdio.h>

#define MAX_LEN 100000

int main() {
    char s[MAX_LEN + 1];
    fgets(s, MAX_LEN, stdin);
    int i = 0;
    char prevChr = '\0';
    while (s[i]) {
        int count = 0, j = i - 1;
        while (s[i] == s[++j])
            ++count;
        putchar(s[i]);
        if (count > 1)
            printf("(%d)", count);

        i += count;
    }
}
#endif

#ifdef T3
#include <stdio.h>

#define MAX_LEN 100000

int main() {
    char s[MAX_LEN + 1];
    fgets(s, MAX_LEN, stdin);
    int i = -1;
    char prevChr = '\0';
    while (s[++i]) {
        if (s[i] != prevChr) {
            putchar(s[i]);
            prevChr = s[i];
        }
    }
}
#endif

#ifdef T2
#include <stdio.h>
#include <malloc.h>

#define MAX_LEN 100001

int main() {
    char *s = (char * ) malloc(MAX_LEN * sizeof(char));
    fgets(s, MAX_LEN, stdin);
    int i = -1, count = 0;

    while (s[++i]) {
        if (s[i] == ' ' || s[i] == '\n') {
            putchar(s[i]);
            continue;
        }

        ++count;
        int j;
        for (j = i; s[j] && s[j] != ' ' && s[j] != '\n'; ++j);
        if (count % 2)
            for (int k = j - 1; k > i - 1; --k)
                putchar(s[k]);
        else
            for (int k = i; k < j; ++k)
                putchar(s[k]);

        i = j - 1;
    }
}
#endif

#ifdef T1
#include <stdio.h>
#include <malloc.h>

#define MAX_LEN 100001

int main() {
    FILE* input = fopen("input.txt", "rt");
    char *word = (char * ) malloc(MAX_LEN * sizeof(char));
    int count = 0;
    while (fscanf(input, "%s", word) != EOF)
        ++count;
    printf("%d\n", count);
    fclose(input);
}
#endif
