#define T

#ifdef T5
#include <stdio.h>

int main() {
    char op = '+';
    int res = 0, a;

    while(scanf("%d", &a)) {
        res += op == '+' ? a : -a;
        scanf("%c", &op);
        if (!op || op == '\n')
            break;
    }
    printf("%d\n", res);
}
#endif

#ifdef T4
#include <stdio.h>

#define MAX_LEN 101

int main() {
    char team1[MAX_LEN], team2[MAX_LEN];
    int a1, a, b1, b, a2, b2;
    scanf("%s - %s %d:%d (%d:%d)", team1, team2, &a, &b, &a1, &b1);
    a2 = a - a1, b2 = b - b1;
    char * res[3], *draw = "draw";
    res[0] = a1 > b1 ? team1 : (a1 < b1 ? team2 : draw);
    res[1] = a2 > b2 ? team1 : (a2 < b2 ? team2 : draw);
    res[2] = a  > b  ? team1 : (a  < b  ? team2 : draw);

    if (res[0] == res[1] && res[1] == res[2])
        printf("%s\n", res[0]);
    else
        printf("%s\n%s\n%s\n", res[0], res[1], res[2]);
}
#endif

#ifdef T3
#include <stdio.h>
#include <string.h>

#define MAX_LEN 10001

int main() {
    char s[MAX_LEN];
    fgets(s, MAX_LEN - 1, stdin);
    int len = (int) strlen(s);
    for (int i = 0, j = len - 1; i < j; ++i, --j) {
        while (s[i] == ' ') ++i;
        while (s[j] == ' ' || s[j] == '\n') --j;
        if (s[i] != s[j]) {
            printf("no\n");
            return 0;
        }
    }
    printf("yes\n");
}
#endif

#ifdef T2
#include <stdio.h>

#define MAX_LEN 10001

int main() {
    char inp[MAX_LEN], start[MAX_LEN], end[MAX_LEN];
    fgets(inp, MAX_LEN - 1, stdin);
    for (int k = 0, s = 0, e = 0; inp[k]; ++k)
        if (inp[k] == '\n');
        else if ('0' <= inp[k] && inp[k] <= '9')
            end[e++] = inp[k];
        else
            start[s++] = inp[k];
    printf("%s%s\n", start, end);
}
#endif

#ifdef T1
#include <stdio.h>

#define MAX_LEN 10002

int main() {
    char inp[MAX_LEN], start[MAX_LEN / 2], end[MAX_LEN / 2];
    fgets(inp, MAX_LEN - 2, stdin);
    for (int k = 0; inp[k]; ++k)
        if (inp[k] == '\n');
        else if (k % 2)
            end[k / 2] = inp[k];
        else
            start[k / 2] = inp[k];
    printf("%s%s\n", start, end);
}
#endif