#define T

#ifdef A
#include <stdio.h>
#include <malloc.h>
#define MAX_EDGES 8

int moves[MAX_EDGES][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
typedef struct g_list_ { int adj[8]; int size; } GList;

void findHamiltonianPath(GList **graph, int n, int pos, int depth, int *complete, int **marked, int **path) {
    (*marked)[pos] = 1;
    if (depth == n*n - 1) *complete = 1;
    for (int i = 0; i < (*graph)[pos].size; ++i) {
        int w = (*graph)[pos].adj[i];
        if (!(*marked)[w])
            findHamiltonianPath(graph, n, w, depth + 1, complete, marked, path);
    }
    if (*complete)
        (*path)[pos] = depth;
    else
        (*marked)[pos] = 0;
}

int main () {
    int n, sx, sy; scanf("%d%d%d", &n, &sx, &sy);
    GList *graph = malloc(n*n * sizeof(GList));

    printf("Graph:");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            GList *v = graph + i * n + j; v->size = 0;  printf("\n%d -", i * n + j);
            for (int k = 0; k < MAX_EDGES; ++k) {
                int i2 = i + moves[k][0], j2 = j + moves[k][1];
                if (0 <= i2 && i2 < n && 0 <= j2 && j2 < n)
                    v->adj[v->size++] = i2 * n + j2, printf(" %d", i2 * n + j2);
            }
        }
    int complete = 0, *marked = calloc(n*n, sizeof(int)), *HamiltonianPath = malloc(n*n * sizeof(int));
    findHamiltonianPath(&graph, n, sx * n + sy, 0, &complete, &marked, &HamiltonianPath);

    printf("\nHamiltonian path:\n");
    if (complete)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                printf("%d ", HamiltonianPath[i*n + j]);
            printf("\n");
        }
    else printf("No way\n");
    free(marked), free(HamiltonianPath), free(graph);
}
#endif

#ifdef B
#include <stdio.h>
#include <malloc.h>

#define MAX_EDGES 4

int moves[MAX_EDGES][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
typedef struct g_list_  { int first[4]; int size; } GList;
typedef struct node_  { int val; struct node_ * next; struct node_ * prev; } * Node;
typedef struct queue_ { Node back; Node front; int size; } Queue;

void enqueue(Queue *q, int v) {
    Node new = malloc(sizeof(struct node_)); ++q->size;
    new->next = q->back; new->prev = NULL; new->val = v;
    if (q->back) q->back->prev = new;
    else q->front = new;
    q->back = new;
}

int dequeue(Queue *q) {
    Node out = q->front;
    int v = out->val;
    q->front->next = NULL; q->front = out->prev; --q->size;
    if (!q->size) q->back = NULL;
    free(out); return v;
}

void BFS(GList **graph, int s, int f, int **maze) {
    Queue queue = {NULL, NULL, 0}; enqueue(&queue, s);
    while (queue.size) {
        int cur = dequeue(&queue);
        if (cur == f) return;
        for (int i = 0; i < (*graph)[cur].size; ++i) {
            int w = (*graph)[cur].first[i];
            if ((*maze)[w] < 0) {
                enqueue(&queue, w);
                (*maze)[w] = (*maze)[cur] + 1;
            }
        }
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    int *maze = malloc(m * n * sizeof(int)), s, f;
    printf("Initial labyrinth:\n");
    for (int i = 0; i < n; ++i) {
        char row[m + 1]; scanf("%s", row);
        printf("%s\n", row);
        for (int j = 0; j < m; ++j) {
            if (row[j] == 'S') s = i * m + j;
            if (row[j] == 'F') f = i * m + j;
            maze[i * m + j] = row[j] == '#' ? 0 : 1;
        }
    }

    GList *graph = malloc(n*m * sizeof(GList));
    printf("Graph:");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            GList *v = graph + i * m + j; v->size = 0; printf("\n%d -", i * m + j);
            if (!maze[i * m + j]) {
                printf(" None");
                continue;
            }
            for (int k = 0; k < MAX_EDGES; ++k) {
                int i2 = i + moves[k][0], j2 = j + moves[k][1];
                if (0 <= i2 && i2 < n && 0 <= j2 && j2 < m && maze[i2 * m + j2])
                    v->first[v->size++] = i2 * m + j2, printf(" %d", i2 * m + j2);
            }
            if (!v->size)
                printf(" None");
        }

    for (int i = 0; i < n * m; ++i) maze[i] = -1; maze[s] = 0;
    BFS(&graph, s, f, &maze);

    printf("\nBFS result is:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            printf("%2d ", maze[i * m + j]);
        printf("\n");
    }
    free(maze);
}
#endif

#ifdef C
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#define INF 1000000000
#define MAX_LEN 25

typedef struct posit_    { int x; int y; } Position;
typedef struct g_node_ { int v; double dist; struct g_node_ * next; } * GNode;
typedef struct g_list_ { GNode first; int size; } GList;
typedef struct node_   { int v; double w; struct node_ *prev; struct node_ *next;} * Node;
typedef struct list_   { Node first; int size; } List;

void add(GList *list, int v) {
    GNode new = malloc(sizeof(struct g_node_));
    new->v = v, new->dist = -1;
    new->next = list->first;
    list->first = new;
    ++list->size;
}

void delete(GList *list) {
    for (GNode gn = list->first; gn; gn = list->first){
        list->first = gn->next;
        free(gn);
    }
}

void push(List *list, int v, double w) {
    Node new = malloc(sizeof(struct node_));
    new->next = list->first;
    new->prev = NULL;
    new->v = v, new->w = w;
    if (list->first)
        list->first->prev = new;
    list->first = new;
    ++list->size;
}

Node popMin(List *list) {
    Node minNode = NULL;
    for (Node cur = list->first; cur; cur = cur->next)
        if (!minNode || cur->w < minNode->w)
            minNode = cur;
    if (!minNode) return NULL;
    --list->size;
    if (minNode == list->first) {
        list->first = minNode->next;
        return minNode;
    }
    if (minNode->next)
        minNode->next->prev = minNode->prev;
    minNode->prev->next = minNode->next;
    minNode->prev = minNode->next = NULL;
    return minNode;
}

int findOrInsert(const char *s, char **src, int *size) {
    for (int i = 0; i < *size; ++i)
        if (strcmp(src[i], s) == 0) return i;
    strcpy(src[(*size)++], s);
    return *size - 1;
}

double distance(Position *p1, Position *p2) {
    return sqrt((p2->x - p1->x)*(p2->x - p1->x) + (p2->y - p1->y)*(p2->y - p1->y));
}

double dijkstra(GList **graph, int n, int start, int dest, int *pathLen, int **path) {
    List unchecked = {NULL, 0};
    Node index[n];
    int prev[n];
    for (int i = 0; i < n; ++i) {
        push(&unchecked, i, (i == start) ? 0 : INF);
        index[i] = unchecked.first;
        prev[i] = -1;
    }
    while (unchecked.size) {
        Node cur = popMin(&unchecked);
        for (GNode gu = (*graph)[cur->v].first; gu; gu = gu->next) {
            Node u = index[gu->v];
            if (u->w > cur->w + gu->dist) {
                u->w = cur->w + gu->dist;
                prev[u->v] = cur->v;
            }
        }
    }
    for (int i = dest; i >= 0; i = prev[i])
        (*path)[(*pathLen)++] = i;
    return prev[dest] >= 0 ? index[dest]->w : -1;
}

int main() {
    int n, size = 0;
    scanf("%d", &n);
    Position pos[n];
    GList *graph = malloc(n * sizeof(GList));

    char **cities = malloc(n * sizeof(char *));
    for (int i = 0; i < n; ++i)
        cities[i] = malloc(MAX_LEN * sizeof(char));


    char tmp[MAX_LEN], ch;
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%s%d%d%c", tmp, &x, &y, &ch);
        int id = findOrInsert(tmp, cities, &size);
        graph[id].size = 0;
        graph[id].first = NULL;
        pos[id].x = x, pos[id].y = y;
        while (ch == ' ')
            ch = (char) getchar();
        while (ch != '\n' && ch != '\r') {
            tmp[0] = ch;
            scanf("%s%c", tmp + 1, &ch);
            int k = findOrInsert(tmp, cities, &size);
            add(graph + id, k);
            while (ch == ' ' || ch == '\r')
                ch = (char) getchar();
        }
    }
    scanf("%s", tmp);
    int start = findOrInsert(tmp, cities, &size);
    scanf("%s", tmp);
    int dest = findOrInsert(tmp, cities, &size);

    for (int i = 0; i < n; ++i)
        for (GNode gu = graph[i].first; gu; gu = gu->next)
            gu->dist = distance(pos + i, pos + gu->v);

    int pathLen = 0, *path = malloc(sizeof(int) * n);
    double totalDist = dijkstra(&graph, n, start, dest, &pathLen, &path);
    if (totalDist > 0) {
        printf("Path is not greater than %d\nPath:\n", (int) ceil(totalDist));
        for (int i = pathLen - 1; i >= 0; --i) {
            printf("%s ", cities[path[i]]);
        }
    } else
        printf("Path:\nNo way");
    printf("\n");

    for (int i = 0; i < n; ++i)
        free(cities[i]);
    free(cities);
    free(path);
    delete(graph);
}
#endif

#ifdef C2
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#define INF 1000000000
#define MAX_LEN 25

typedef struct posit_  { int x; int y; } Position;
typedef struct g_node_ { int v; double dist; struct g_node_ * next; } * GNode;
typedef struct g_list_ { GNode first; int size; } GList;

void add(GList *list, int v) {
    GNode new = malloc(sizeof(struct g_node_));
    new->v = v, new->dist = -1;
    new->next = list->first, list->first = new;
    ++list->size;
}

int findOrInsert(const char *s, char **src, int *size) {
    for (int i = 0; i < *size; ++i)
        if (strcmp(src[i], s) == 0) return i;
    strcpy(src[(*size)++], s);
    return *size - 1;
}

double distance(Position *p1, Position *p2) {
    return sqrt((p2->x - p1->x)*(p2->x - p1->x) + (p2->y - p1->y)*(p2->y - p1->y));
}

double dijkstra(GList **graph, int n, int start, int dest, int *pathLen, int **path) {
    int unchecked[n], prev[n], min = start;
    double weights[n];
    for (int i = 0; i < n; ++i) {
        unchecked[i] = 1;
        weights[i] = INF;
        prev[i] = -1;
    }
    weights[start] = 0;
    while (min >= 0) {
        unchecked[min] = 0;
        for (GNode gu = (*graph)[min].first; gu; gu = gu->next) {
            if (weights[gu->v] > weights[min] + gu->dist) {
                weights[gu->v] = weights[min] + gu->dist;
                prev[gu->v] = min;
            }
        }
        min = -1;
        for (int i = 0; i < n; ++i)
            if (unchecked[i] && (min < 0 || weights[i] < weights[min]))
                min = i;
    }
    for (int i = dest; i >= 0; i = prev[i])
        (*path)[(*pathLen)++] = i;
    return prev[dest] >= 0 ? weights[dest] : -1;
}

int main() {
    int n, size = 0;
    scanf("%d", &n);
    Position pos[n];
    GList *graph = malloc(n * sizeof(GList));

    char **cities = malloc(n * sizeof(char *));
    for (int i = 0; i < n; ++i)
        cities[i] = malloc(MAX_LEN * sizeof(char));


    char tmp[MAX_LEN], ch;
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%s%d%d%c", tmp, &x, &y, &ch);
        int id = findOrInsert(tmp, cities, &size);
        graph[id].size = 0;
        graph[id].first = NULL;
        pos[id].x = x, pos[id].y = y;
        while (ch == ' ')
            ch = (char) getchar();
        while (ch != '\n' && ch != '\r') {
            tmp[0] = ch;
            scanf("%s%c", tmp + 1, &ch);
            int k = findOrInsert(tmp, cities, &size);
            add(graph + id, k);
            while (ch == ' ' || ch == '\r')
                ch = (char) getchar();
        }
    }
    scanf("%s", tmp);
    int start = findOrInsert(tmp, cities, &size);
    scanf("%s", tmp);
    int dest = findOrInsert(tmp, cities, &size);

    for (int i = 0; i < n; ++i)
        for (GNode gu = graph[i].first; gu; gu = gu->next)
            gu->dist = distance(pos + i, pos + gu->v);

    int pathLen = 0, *path = malloc(sizeof(int) * n);
    double totalDist = dijkstra(&graph, n, start, dest, &pathLen, &path);

    if (totalDist > 0) {
        printf("Path is not greater than %d\nPath:\n", (int) ceil(totalDist));
        for (int i = pathLen - 1; i >= 0; --i)
            printf("%s ", cities[path[i]]);
    } else
        printf("Path:\nNo way");
    printf("\n");

    for (int i = 0; i < n; ++i)
        for (GNode gn = graph[i].first; gn; gn = graph[i].first)
            graph[i].first = gn->next, free(gn);
    for (int i = 0; i < n; ++i) free(cities[i]);
    free(cities), free(path), free(graph);
}
#endif

