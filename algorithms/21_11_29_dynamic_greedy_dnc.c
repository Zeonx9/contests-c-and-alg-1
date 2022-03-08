#define T

#ifdef A
#include <stdio.h>

int main() {
    int n; scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);

    int dp[n], prev[n]; dp[0] = 1, prev[0] = -1;
    for (int i = 1; i < n; ++i) {
        int m = prev[i] = -1;
        for (int j = 0; j < i; ++j)
            if (arr[j] <= arr[i] && dp[j] > m || arr[j] <= arr[i] && dp[j] == m && arr[j] < arr[prev[i]])
                m = dp[j], prev[i] = j;
        dp[i] = m < 0 ? 1 : m + 1;
    }

    int pathLen = 1, endOfPath = 0;
    for (int i = 1; i < n; ++i)
        if (dp[i] > pathLen || dp[i] == pathLen && arr[i] < arr[endOfPath])
            pathLen = dp[i], endOfPath = i;

    printf("Best length = %d\nBest combo is: ", pathLen);
    int path[pathLen];
    for (int i = pathLen - 1, j = endOfPath; i >= 0; --i)
        path[i] = arr[j], j = prev[j];

    for (int i = 0; i < pathLen; ++i)
        printf(" %d", path[i]);
}
#endif

#ifdef B
#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 300

typedef struct point_ { int x; int y; } * Point;

Point initPoint(int x, int y) {
    Point point = (Point ) malloc(sizeof(struct point_));
    point->x = x, point->y = y;
    return point;
}

int distance(Point start, Point end, Point this) {
    return (start->y - end->y) * (this->x - start->x) + (end->x - start->x) * (this->y - start->y);
}

int comparePoints(Point a, Point b) {
    return a->x > b->x ? 1 : (a->x == b->x ? (a->y > b->y ? 1 : (a->y == b->y ? 0 : -1)) : -1);
}

void mergeSortPoints(Point *arr, int len) {
    if (len < 2) return;
    int ls = len / 2;
    Point tmp[ls];
    for (int i = 0; i < ls; ++i) tmp[i] = arr[i];

    mergeSortPoints(tmp, ls);
    mergeSortPoints(arr + ls, len - ls);
    for (int k = 0, l = 0, r = ls; k < len; ++k)
        arr[k] = l < ls && r < len && comparePoints(tmp[l], arr[r]) < 0 || r == len ?
                 tmp[l++] : arr[r++];
}

void setPoints(Point * points, int len, Point start, Point end, Point **spot) {
    Point above[len], maxPoint = NULL;
    int aboveSize = 0, maxDist;

    for (int i = 0; i < len; ++i) {
        int dist = distance(start, end, points[i]);
        if (dist > 0) above[aboveSize++] = points[i];
        if (!maxPoint || dist && dist > maxDist)
            maxDist = dist, maxPoint = points[i];
    }
    if (!aboveSize)
        return;

    *(*spot)++ = maxPoint;
    setPoints(above, aboveSize, start, maxPoint, spot);
    setPoints(above, aboveSize, maxPoint, end, spot);
}

int main() {
    Point points[MAX_SIZE], left = NULL, right = NULL;
    int n = 0;
    FILE *inputFile = fopen("input.txt", "rt");
    for (int x, y, i = 0; (fscanf(inputFile, "%d %d", &x, &y)) != EOF; ++i, n = i) {
        points[i] = initPoint(x, y);
        if (!left  || comparePoints(left,  points[i]) > 0) left  = points[i];
        if (!right || comparePoints(right, points[i]) < 0) right = points[i];
    }
    fclose(inputFile);

    Point convexHull[n], *spot = convexHull + 2;
    convexHull[0] = left, convexHull[1] = right;

    setPoints(points, n, left, right, &spot);
    setPoints(points, n, right, left, &spot);

    int m = (int) (spot - convexHull);
    mergeSortPoints(convexHull, m);
    printf("Convex Hull is:\n");
    for (int i = 0; i < m; ++i)
        printf("%d %d\n", convexHull[i]->x, convexHull[i]->y);

    for (int i = 0; i < n; ++i)
        free(points[i]);
}
#endif

#ifdef B2
#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 10000

typedef struct point_ { int x; int y; } * Point;
typedef Point T;

typedef struct g_node_ { T val; struct g_node_ * next; } * GNode;
typedef struct stack_ { GNode top; int size; } * Stack;

Stack initStack() {
    Stack stack = (Stack ) malloc(sizeof(struct stack_));
    stack->top = NULL; stack->size = 0;
    return stack;
}

void push(Stack stack, T val) {
    GNode new = (GNode ) malloc(sizeof(struct g_node_));
    new->val = val; new->next = stack->top;
    stack->top = new, ++stack->size;
}

T pop(Stack stack) {
    GNode out = stack->top; T res = out->val;
    stack->top = stack->top->next; --stack->size;
    free(out);
    return res;
}

T peek(Stack stack, int depth) {
    GNode this = stack->top;
    for (int i = 1; i < depth; ++i)
        this = this->next;
    return this->val;
}

void swap(Point *a, Point *b){
    Point tmp = *a; *a = *b, *b = tmp;
}

int dist(Point a, Point b) {
    return (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y);
}

int isLeft(Point start, Point end1, Point end2) {
    return (end1->y - start->y) * (end2->x - start->x) - (end1->x - start->x) * (end2->y - start->y);
}

void mergeSortPoints(Point *arr, int size, Point pivot, int sortByValue) {
    if (size < 2) return;
    int tmpSize = size / 2;
    T tmp[tmpSize];
    for (int i = 0; i < tmpSize; ++i)
        tmp[i] = arr[i];

    mergeSortPoints(tmp, tmpSize, pivot, sortByValue);
    mergeSortPoints(arr + tmpSize, size - tmpSize, pivot, sortByValue);

    for (int k = 0, l = 0, r = tmpSize; k < size; ++k)
        if (sortByValue)
            arr[k] = l < tmpSize && r < size && (tmp[l]->x < arr[r]->x || tmp[l]->x == arr[r]->x && tmp[l]->y < arr[r]->y)  || r == size ?
                    tmp[l++] : arr[r++];
        else {
            int angle =  l < tmpSize && r < size ? isLeft(pivot, tmp[l], arr[r]) : 0;
            arr[k] = l < tmpSize && r < size && (angle < 0 || angle == 0 && dist(pivot, tmp[l]) < dist(pivot, arr[r])) || r == size ?
                     tmp[l++] : arr[r++];
        }
}

int main() {// NOLINT(cert-err34-c)
    Point points[MAX_SIZE];
    int n, x, y;
    FILE *inputFile = fopen("input.txt", "rt");
    for (n = 0; (fscanf(inputFile, "%d %d", &x, &y)) != EOF; ++n) {
        Point point = (Point ) malloc(sizeof(struct point_));
        point->x = x, point->y = y;
        points[n] = point;
    }
    fclose(inputFile);

    int minIndByX = 0;
    for (int i = 1; i < n; ++i)
        if (points[minIndByX]->x > points[i]->x)
            minIndByX = i;
    swap(points, points + minIndByX);

    mergeSortPoints(points + 1, n - 1, points[0], 0);

    Stack convexHull = initStack();
    push(convexHull, points[0]), push(convexHull, points[1]);

    for (int i = 2; i < n; ++i) {
        while (convexHull->size > 1 && isLeft(peek(convexHull, 1), peek(convexHull, 2), points[i]) <= 0 ) {
            Point p = pop(convexHull);
            free(p);
        }
        push(convexHull, points[i]);
    }

    n = convexHull->size;
    for (int i = n - 1; i > -1; --i)
        points[i] = pop(convexHull);
    free(convexHull);
    mergeSortPoints(points, n, NULL, 1);

    printf("Convex Hull is:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d %d\n", points[i]->x, points[i]->y);
        free(points[i]);
    }
}
#endif

#ifdef C
#include <stdio.h>
#include <string.h>

#define MAX_LEN 10000

int minOfThree(int a, int b, int c) {
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int editDistance(const char * s1, const char * s2, int n, int m) {
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 1; j <= m; ++j) dp[0][j] = j;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[i][j] = s1[i - 1] == s2[j - 1] ? dp[i - 1][j - 1] :
                    1 + minOfThree(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
    return dp[n][m];
}

int main() {
    char origin[MAX_LEN + 1];
    int n; scanf("%s%d", origin, &n);
    char variants[n][MAX_LEN + 1];
    int distance[n], ol = (int) strlen(origin), count, minDist = MAX_LEN;
    for (int i = 0; i < n; ++i) {
        scanf("%s", variants[i]);
        int vl = (int) strlen(variants[i]);
        distance[i] = editDistance(variants[i], origin, vl, ol);
        if (distance[i] == minDist)
            ++count;
        else if (distance[i] < minDist)
            minDist = distance[i], count = 1;
    }
    printf("Most similar words = %d\nMinimal operations needed = %d\n", count, minDist);
    for (int i = 0; i < n; ++i)
        if (distance[i] == minDist)
            printf("%s\n", variants[i]);
}
#endif

#ifdef D
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 12

typedef struct { int i; int j; } Cell;

int main() {
    int n, m; scanf("%d%d", &n, &m);
    int money[n][m];
    Cell s;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            char cur[MAX_LEN]; scanf("%s", cur);
            if (cur[0] == 'S')
                s.i = i, s.j = j, money[i][j] = 0;
            else
                money[i][j] = atoi(cur);
        }

    for (int j = s.j + 1; j < m; ++j)
        money[s.i][j] += money[s.i][j - 1];
    for (int i = s.i + 1; i < n; ++i)
        money[i][s.j] += money[i - 1][s.j];
    for (int i = s.i + 1; i < n; ++i)
        for (int j = s.j + 1; j < m; ++j)
            money[i][j] += money[i - 1][j] > money[i][j - 1] ? money[i - 1][j] : money[i][j - 1];

    int pathLen = n + m - s.i - s.j - 1; Cell path[pathLen];
    path[pathLen - 1] = (Cell ) {n - 1, m - 1};
    for (int k = pathLen - 2; k > -1; --k) {
        int i = path[k + 1].i, j = path[k + 1].j;
        path[k] = i > s.i && j > s.j && money[i - 1][j] >= money[i][j - 1] || j == s.j ?
                (Cell) {i - 1, j} : (Cell ) {i, j - 1};
    }

    printf("Path:\n");
    for (int k = 0; k < pathLen; ++k)
        printf("(%d,%d) ", path[k].i, path[k].j);
    printf("\nCoins: %d\n", money[n - 1][m - 1]);
}
#endif

#ifdef E
#include <stdio.h>

int main() {
    int n; scanf("%d", &n);
    int prices[n][n];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", prices[i] + j);

    int paths[n][n + 1], costs[n], visited[n], result = -1;
    for (int start = 0; start < n; ++start) {
        for (int i = 0; i < n; ++i)
            visited[i] = 0;
        costs[start] = 0;

        int cur = start, lost = 0, cost;
        for (int i = 0; i < n; ++i) {
            visited[cur] = 1, paths[start][i] = cur;
            if (i == n - 1) visited[start] = 0;

            int next = -1; cost = 0;
            for (int x = 0; x < n; ++x) {
                if (!prices[cur][x] || visited[x])
                    continue;
                if (next < 0 || cost > prices[cur][x])
                    next = x, cost = prices[cur][x];
            }

            if (next < 0) { lost = 1; break; }
            else cur = next, costs[start] += cost;
        }
        if (lost) costs[start] = -1;
        else {
            paths[start][n] = start;
            if (result < 0 || costs[result] > costs[start])
                result = start;
        }
    }

    if (result < 0)
        printf("Lost\n");
    else {
        printf("Path:\n");
        for (int i = 0; i < n + 1; ++i)
            printf("%d ", paths[result][i]);
        printf("\nCost: %d\n", costs[result]);
    }
}
#endif
