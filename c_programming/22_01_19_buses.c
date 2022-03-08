#define T1

#ifdef T
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define NAME_LEN 51
#define MAX_BUSES 10
#define MAX_STOPS 30
#define WRONG_F "WRONG %s FORMAT\n"
#define NO_BUS "BUS %s DOESN'T EXIST\n"
#define FIND_BUSES "BUSES FROM %s TO %s:\n"
char commandsStr[][6] = {"ADD", "PRINT", "FIND", "BUS", "STOP", "ALL"};
enum commands {add, print, find, bus, stop, all};

typedef struct {
    char name[NAME_LEN];
    char * buses[MAX_BUSES];
    int busCount;
} Stop;
typedef struct {
    char number[6];
    char * stops[MAX_STOPS];
    int stopCount;
} Bus;

Stop stops[MAX_STOPS * MAX_BUSES] = {};
Bus buses[MAX_BUSES] = {};
int busCount = 0, stopCount = 0;
FILE *input, *output;

int getCommand(const char * c){
    for (int i = 0; i < 6; ++i)
        if (strcmp(commandsStr[i], c) == 0) return i;
    return -1;
}
Bus * findBus(const char * s) {
    for (int i = 0; i < busCount; ++i)
        if(strcmp(buses[i].number, s) == 0) return &buses[i];
    return NULL;
}
Stop * findStop(const char * s) {
    for (int i = 0; i < stopCount; ++i)
        if(strcmp(stops[i].name, s) == 0) return &stops[i];
    return NULL;
}
Stop * findBusStop(Bus * b, char * name) {
    for (int i = 0; i < b->stopCount; ++i)
        if (strcmp(b->stops[i], name) == 0) return findStop(name);
    return NULL;
}
int addBus(const char * s){
    if (busCount == MAX_BUSES) return 0;
    strcpy(buses[busCount++].number, s);
    return 1;
}
int addBusStop(Bus * b, Stop * s) {
    if (b->stopCount == MAX_STOPS) return 0;
    b->stops[b->stopCount++] = s->name;
    s->buses[s->busCount++] = b->number;
    return 1;
}
void printBus(Bus * b) {
    fprintf(output, "%s\nSTOPS: ", b->number);
    for (int i = 0; i < b->stopCount; ++i)
        fprintf(output, "%s ", b->stops[i]);
    fprintf(output, "\n");
}
void printStop(Stop * s, const char * name) {
    fprintf(output, "%s: ", name);
    if (!s || !s->busCount) fprintf(output, "NO BUSES GO TO STOP");
    else for (int i = 0; i < s->busCount; ++i)
            fprintf(output, "%s ", s->buses[i]);
    fprintf(output, "\n");
}
int hasCommonStop(Bus *b1, Bus *b2) {
    for (int i = 0; i < b1->stopCount; ++i)
        for (int j = 0; j < b2->stopCount; ++j)
            if (strcmp(b1->stops[i], b2->stops[j]) == 0) return 1;
    return 0;
}
char ** findPath(char * name1, char * name2, int *len) {
    char ** res = malloc(MAX_BUSES * sizeof(char *)); *len = 0;
    for (int i = 0; i < busCount; ++i)
        if (findBusStop(buses + i, name1) && findBusStop(buses + i, name2))
            res[(*len)++] = buses[i].number;
    return res;
}

typedef struct { char *b1, *b2; } TransferPath;
TransferPath * findTransferPath(char * name1, char * name2, int *len) {
    TransferPath * tp = malloc(90 * sizeof(TransferPath)); *len = 0;
    Stop *stop1 = findStop(name1), *stop2 = findStop(name2);
    Bus *bus1, *bus2;
    if (!stop1 || !stop2) return NULL;
    for (int i = 0; i < stop1->busCount; ++i) {
        bus1 = findBus(stop1->buses[i]);
        for (int j = 0; j < stop2->busCount; ++j) {
            bus2 = findBus(stop2->buses[j]);
            if (hasCommonStop(bus1, bus2))
                tp[(*len)++] = bus1 < bus2 ? (TransferPath) {bus1->number, bus2->number } :
                                             (TransferPath) {bus2->number, bus1->number };
        }
    }
    return tp;
}

int main() {
    input = fopen("input.txt", "r"), output = fopen("output.txt", "w");
    char arg1[6] = "", arg2[NAME_LEN] = "", arg3[NAME_LEN] = "", arg4[NAME_LEN] = "";
    char commandStr[200];
    Bus *curBus; Stop *curStop;

    while (fgets(commandStr, 200, input) != NULL) {
        sscanf(commandStr, "%s %s %s %s", arg1, arg2, arg3, arg4);
        switch (getCommand(arg1)) {
            case add: {
                switch (getCommand(arg2)) {
                    case bus: {
                        if (*arg4 || !*arg3) { fprintf(output, WRONG_F, commandsStr[add]); break; }
                        if (!findBus(arg3)) {
                            if (!addBus(arg3)) fprintf(output, "CAN'T ADD BUS %s. BUSPARK IS FULL\n", arg3);
                        } else fprintf(output, "BUS %s ALREADY EXISTS\n", arg3);
                    } break;
                    case stop: {
                        if (!*arg4 || !*arg3) { fprintf(output, WRONG_F, commandsStr[add]); break; }
                        curBus = findBus(arg3); curStop = findStop(arg4);
                        if (!curStop) {
                            strcpy(stops[stopCount].name, arg4);
                            curStop = &stops[stopCount++];
                        }
                        if (curBus){
                            if (!findBusStop(curBus, arg4)) {
                                if (!addBusStop(curBus, curStop))
                                    fprintf(output, "CAN'T ADD STOP %s TO BUS %s. BUS IS FULL\n", arg4, arg3);
                            } else fprintf(output, "BUS %s ALREADY HAS STOP %s\n", arg3, arg4);
                        } else fprintf(output, NO_BUS, arg3);
                    } break;
                    default: fprintf(output, WRONG_F, commandsStr[add]);
                }
            } break;

            case print: {
                switch (getCommand(arg2)) {
                    case bus: {
                        if (*arg4 || !*arg3) { fprintf(output, WRONG_F, commandsStr[print]); break; }
                        curBus = findBus(arg3);
                        if (!curBus) fprintf(output, NO_BUS, arg3);
                        else printBus(curBus);
                    } break;
                    case stop: {
                        if (*arg4 || !*arg3) { fprintf(output, WRONG_F, commandsStr[print]); break; }
                        printStop(findStop(arg3), arg3);
                    } break;
                    case all: {
                        for (int i = 0; i < busCount; ++i) printBus(&buses[i]);
                    } break;
                    default: fprintf(output, WRONG_F, commandsStr[print]);
                }
            } break;

            case find: {
                if (!*arg2 || !*arg3 || *arg4) { fprintf(output, WRONG_F, commandsStr[find]); break; }
                if (strcmp(arg2, arg3) == 0) { fprintf(output, "STOPS %s ARE THE SAME\n", arg2); break; }
                int foundCount;
                char **foundBuses = findPath(arg2, arg3, &foundCount);
                if (foundCount) {
                    fprintf(output, FIND_BUSES, arg2, arg3);
                    for (char **b = foundBuses; b - foundBuses < foundCount; ++b)
                        fprintf(output, "%s\n", *b);
                } else {
                    TransferPath *tp = findTransferPath(arg2, arg3, &foundCount);
                    if (foundCount) {
                        fprintf(output, FIND_BUSES, arg2, arg3);
                        for (TransferPath *b = tp; b - tp < foundCount; ++b)
                            fprintf(output, "%s %s\n", b->b1, b->b2);
                    } else fprintf(output, "THERE ARE NO BUSES FROM %s TO %s\n", arg2, arg3);
                    free(tp);
                } free(foundBuses);
            } break;
            default: fprintf(output, "ERROR\n");
        }
        *arg1 = *arg2 = *arg3 = *arg4 = '\0';
    }
}
#endif