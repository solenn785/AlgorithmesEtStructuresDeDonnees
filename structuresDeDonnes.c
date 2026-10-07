#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX 100

/* ---------- array ---------- */
typedef struct {
    int data[MAX];
    int size;
} Array;

void array_insert(Array *a, int i, int x) {
    for (int j = a->size - 1; j >= i; j--)   
        a->data[j + 1] = a->data[j];
    a->data[i] = x;
    a->size++;
}

void array_delete(Array *a, int i) {
    for (int j = i; j < a->size - 1; j++)   
        a->data[j] = a->data[j + 1];
    a->size--;
}

/* ---------- simple list  ---------- */
typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *list_push_front(Node *head, int x) {
    Node *n = malloc(sizeof(Node));
    n->value = x;
    n->next = head;
    return n;                                
}

Node *list_pop_front(Node *head) {
    Node *next = head->next;
    free(head);
    return next;
}

/* ----------  double list  ---------- */
typedef struct DNode {
    int value;
    struct DNode *prev;
    struct DNode *next;
} DNode;

DNode *dlist_push_front(DNode *head, int x) {
    DNode *n = malloc(sizeof(DNode));
    n->value = x;
    n->prev = NULL;
    n->next = head;
    if (head != NULL) head->prev = n;
    return n;
}

/* ----------  circular list  ---------- */
/* même Node que la liste simple, mais le dernier pointe vers la tête */
Node *circ_push_back(Node *head, int x) {
    Node *n = malloc(sizeof(Node));
    n->value = x;
    if (head == NULL) {
        n->next = n;                         /* il pointe sur lui-même */
        return n;
    }
    Node *last = head;
    while (last->next != head) last = last->next;
    last->next = n;
    n->next = head;
    return head;
}

/* ---------- Stacks (LIFO) ---------- */
typedef struct {
    int data[MAX];
    int size;
} Stack;

void push(Stack *s, int x) { s->data[s->size] = x; s->size++; }
int  pop(Stack *s)         { s->size--; return s->data[s->size]; }
int  peek(Stack *s)        { return s->data[s->size - 1]; }

/* ---------- FILE (FIFO), circular ---------- */
typedef struct {
    int data[MAX];
    int front;   /* indice du premier élément */
    int size;
} Queue;

void enqueue(Queue *q, int x) {
    q->data[(q->front + q->size) % MAX] = x;  /* % MAX : on reboucle */
    q->size++;
}

int dequeue(Queue *q) {
    int x = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return x;
}

/* ---------- Queues ---------- */
typedef struct {
    int value[MAX];
    int priority[MAX];
    int size;
} PQueue;

void pq_enqueue(PQueue *q, int value, int priority) {
    q->value[q->size] = value;
    q->priority[q->size] = priority;
    q->size++;
}

int pq_dequeue(PQueue *q) {                 
    int best = 0;
    for (int i = 1; i < q->size; i++)
        if (q->priority[i] > q->priority[best]) best = i;
    int x = q->value[best];
    for (int i = best; i < q->size - 1; i++) {   
        q->value[i] = q->value[i + 1];
        q->priority[i] = q->priority[i + 1];
    }
    q->size--;
    return x;
}

/* ---------- hashtables ---------- */
#define HSIZE 4

typedef struct Entry {
    char key[32];
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *buckets[HSIZE];
} HashTable;

int hash(const char *key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) sum += key[i];
    return sum % HSIZE;
}

void ht_put(HashTable *t, const char *key, int value) {
    int i = hash(key);
    Entry *e = malloc(sizeof(Entry));
    strcpy(e->key, key);
    e->value = value;
    e->next = t->buckets[i];                
    t->buckets[i] = e;
}

int ht_get(HashTable *t, const char *key) {  /* -1 si absent */
    for (Entry *e = t->buckets[hash(key)]; e != NULL; e = e->next)
        if (strcmp(e->key, key) == 0) return e->value;
    return -1;
}
