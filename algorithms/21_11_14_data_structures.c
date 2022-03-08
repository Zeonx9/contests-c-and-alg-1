#define T

#ifdef T1
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct token_ { char symbol; int value; } Token;
typedef Token T;

struct g_node_ { T data; struct g_node_ * next; };
typedef struct g_node_ *GNode;


struct stack_ { GNode head; int size; };
typedef struct stack_ *Stack;

GNode initNode(T data, GNode next){
    GNode node_ = (GNode ) malloc(sizeof(struct g_node_));
    node_->data = data, node_->next = next;
    return node_;
}
Stack initStack() {
    Stack stack = (Stack) malloc(sizeof(struct stack_));
    stack->head = NULL, stack->size = 0;
    return stack;
}

int isEmpty(Stack stack) { return !stack->size; }

void push(Stack stack, T element) {
    GNode this = initNode(element, stack->head);
    stack->head = this;
    ++stack->size;
}

T pop(Stack stack) {
    GNode this = stack->head;
    stack->head = stack->head->next;
    --stack->size;
    T res = this->data;
    free(this);
    return res;
}

T peek(Stack stack) { return stack->head->data; }

Token * tokenize(const char *str, int * outSize) {
    Token * out = (Token * ) malloc(strlen(str) * sizeof(Token));
    int t = 0;
    for (int i = 0; str[i]; ++i, ++t) {
        int value = 0, len = 0;
        switch (str[i]) {
            case '+': out[t] = (Token) {'+', 1}; break;
            case '-': out[t] = (Token) {'-', 1}; break;
            case '*': out[t] = (Token) {'*', 2}; break;
            case '/': out[t] = (Token) {'/', 2}; break;
            case '(': out[t] = (Token) {'(', 0}; break;
            case ')': out[t] = (Token) {')', 3}; break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                while ('0' <= str[i + len] && str[i + len] <= '9') {
                    value = value * 10 + str[i + len] - '0';
                    ++len;
                }
                out[t] = (Token) {'\0', value};
                i += len - 1;
                break;
            default:
                --t;
        }
    }
    *outSize = t;
    return out;
}

char * toReversePolishNotation(char * str) {
    int len;
    Token * tokens = tokenize(str, &len);
    Stack stack = initStack();
    char * out = (char * ) malloc((2 * len + 1) * sizeof(char)), *tmp = out;
    for (int i = 0; i < len; ++i){
        if (!tokens[i].symbol) {
            tmp += sprintf(tmp, "%d ", tokens[i].value);
            continue;
        }
        while (tokens[i].symbol != '(' && !isEmpty(stack) && peek(stack).value >= tokens[i].value)
            tmp += sprintf(tmp, "%c ", pop(stack).symbol);

        if (tokens[i].symbol == ')') {
            while (peek(stack).value)
                tmp += sprintf(tmp, "%c ", pop(stack).symbol);
            pop(stack);
        } else
            push(stack, tokens[i]);
    }
    while (!isEmpty(stack))
        tmp += sprintf(tmp, "%c ", pop(stack).symbol);

    free(stack), free(tokens);
    return out;
}

int calculate(char * str) {
    int len;
    Token * tokens = tokenize(str, &len);
    Stack numbers = initStack();
    for (int i = 0; i < len; ++i) {
        if (!tokens[i].symbol)
            push(numbers, tokens[i]);
        else {
            Token b = pop(numbers), a = pop(numbers);
            int res;
            switch (tokens[i].symbol) {
                case '+': res = a.value + b.value; break;
                case '-': res = a.value - b.value; break;
                case '*': res = a.value * b.value; break;
                case '/': res = a.value / b.value; break;
            }
            Token c = {'\0', res};
            push(numbers, c);
        }
    }
    int res = pop(numbers).value;
    free(numbers), free(tokens);
    return res;
}

int main(){
    char expr[100];
    scanf("%s", expr);
    printf("Expression:\n%s\n", expr);
    char *rpn = toReversePolishNotation(expr);
    printf("Reverse Polish Notation:\n%s\n", rpn);
    printf("Result:\n%d\n", calculate(rpn));
}
#endif

#ifdef T2
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LOG_START "key=%s hash=%d operation=%s"
#define LOG_COLLISION  " result=collision linear_probing=%d"
#define MAX_KEY_LEN 30

struct pair_ { char * key; int val; };
typedef struct pair_ *Pair;

struct hash_table_ { Pair * data; int * deleted; };
typedef struct hash_table_ * HTable;

int p = 0, q = 0, *ps;
int hash(const char *key) {
    int s = 0;
    for (int i = 0; key[i]; ++i)
        s += (key[i] - 'a' + 1) * ps[i];
    return s % q;
}

HTable initHTable() {
    HTable table = (HTable) malloc(sizeof(struct hash_table_));
    table->data = (Pair * ) calloc(q, sizeof(Pair));
    table->deleted = (int * ) calloc(q, sizeof(int));

    ps = (int * ) malloc(MAX_KEY_LEN * sizeof(int)), ps[0] = 1;
    for (int i = 1; i < MAX_KEY_LEN; ++i)
        ps[i] = (ps[i - 1] * p) % q;
    return table;
}

int linearProbing(HTable table, int i, int *found, const char * key) {
    for (int j = 0; j < q; ++j, i = (i + 1) % q)
        if (table->data[i] && strcmp(table->data[i]->key, key) == 0) {
            *found = 1;
            return i;
        }
        else if (!table->data[i] && !table->deleted[i])
            break;
    *found = 0;
    return i;
}

void get(HTable table, const char * key) {
    int hsh = hash(key), i = hsh;
    int collision = table->deleted[i] || table->data[i] && strcmp(table->data[i]->key, key) != 0;
    int found = table->data[i] && strcmp(table->data[i]->key, key) == 0;
    i = collision ? linearProbing(table, hsh, &found, key) : i;

    printf(LOG_START,  key, hsh, "GET");
    printf(collision ? LOG_COLLISION : found ? " result=found" : " result=no_key", i);
    printf(found ? " value=%d\n" : collision ? " value=no_key\n" : "\n", found ? table->data[i]->val : 0);
}

void put(HTable table, const char * key, int value){
    int hsh = hash(key), i = hsh;
    int collision = table->data[i] && strcmp(table->data[i]->key, key) != 0, found = !collision;
    if (collision)
        for (int j = 0; j < q; ++j, i = (i + 1) % q)
            if (!table->data[i] || strcmp(table->data[i]->key, key) == 0) {
                found = 1;
                break;
            }

    printf(LOG_START,  key, hsh, "PUT");
    if (found) {
        if (table->data[i]) {
            table->data[i]->val = value;
        } else {
            Pair new = (Pair) malloc(sizeof(struct pair_));
            char * cpy = (char *) malloc((strlen(key) + 1) * sizeof(char));
            strcpy(cpy, key);
            new->key = cpy, new->val = value;
            table->data[i] = new;
            table->deleted[i] = 0;
        }
        printf(collision ? LOG_COLLISION : " result=inserted" , i);
        printf(" value=%d\n", value);
    } else
        printf(" result=overflow\n");
}

void delete(HTable table, const char * key) {
    int hsh = hash(key), i = hsh;
    int collision = table->deleted[i] || table->data[i] && strcmp(table->data[i]->key, key) != 0;
    int found = table->data[i] && strcmp(table->data[i]->key, key) == 0;
    i = collision ? linearProbing(table, hsh, &found, key) : i;

    if (found) {
        free(table->data[i]);
        table->data[i] = NULL;
        table->deleted[i] = 1;
    }
    printf(LOG_START,  key, hsh, "DEL");
    printf(collision ? LOG_COLLISION " value=%s\n" : found ? " result=removed\n" : " result=no_key\n",
           i, found ? "removed" : "no_key");
}

int main() {
    int n;
    scanf("%d%d%d", &q, &p, &n); // NOLINT(cert-err34-c)
    HTable table = initHTable();

    for (int i = 0; i < n; ++i) {
        char action[4], key[100];
        scanf("%s%s", action, key);
        switch (action[0]) {
            case 'G': get(table, key); break;
            case 'D': delete(table, key); break;
            case 'P': {
                int value;
                scanf("%d", &value); // NOLINT(cert-err34-c)
                put(table, key, value);
            }
        }
    }
    for (int i = 0; i < q; ++i)
        if (table->data[i])
            free(table->data[i]->key), free(table->data[i]);
    free(table->deleted), free(table->data), free(ps), free(table);
}
#endif