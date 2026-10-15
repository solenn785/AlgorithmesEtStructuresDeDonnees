#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structuresDeDonnees.h"

//arrays

Array newArray(){
    Array a = malloc(sizeof(struct SArray));
    a->size = 0;
return a;
}
 
void freeArray(Array a){
    free(a);
}
 
int array_length(Array a){
return a->size;
}
 
int array_get(Array a, int index){
return a->tab[index];
}
 
void array_set(Array a, int index, int value){
    a->tab[index] = value;
}
 
void array_append(Array a, int value){
    a->tab[a->size] = value;
    a->size = a->size + 1;
}
 
void array_insertAt(Array a, int index, int value){
    int i;
    for(i = a->size; i > index; i--){
        a->tab[i] = a->tab[i-1];
    }
    a->tab[index] = value;
    a->size = a->size + 1;
}
 
void array_removeAt(Array a, int index){
    int i;
    for(i = index; i < a->size - 1; i++){
        a->tab[i] = a->tab[i+1];
    }
    a->size = a->size - 1;
}
 
int array_indexOf(Array a, int value){
    int i;
    for(i = 0; i < a->size; i++){
        if(a->tab[i] == value) return i;
    }
return -1;
}
 
void array_print(Array a){
    int i;
    for(i = 0; i < a->size; i++){
        printf("%i ", a->tab[i]);
    }
    printf("\n");
}

//stack

Stack newStack(){
    Stack s = malloc(sizeof(struct SStack));
    s->ptr = 0;
return s;
}
 
void freeStack(Stack s){
    free(s);
}
 
void stack_push(Stack s, int value){
    s->tab[s->ptr] = value;
    s->ptr = s->ptr + 1;
}
 
int stack_top(Stack s){
return s->tab[s->ptr-1];
}
 
void stack_pop(Stack s){
    s->ptr = s->ptr - 1;
}
 
void stack_add(Stack s){
    int v1; int v2;
    v1 = stack_top(s);
    stack_pop(s);
    v2 = stack_top(s);
    stack_pop(s);
    stack_push(s, v1+v2);
}
 
void stack_sub(Stack s){
    int v1; int v2;
    v1 = stack_top(s);
    stack_pop(s);
    v2 = stack_top(s);
    stack_pop(s);
    stack_push(s, v1-v2);
}
 
void stack_mult(Stack s){
    int v1; int v2;
    v1 = stack_top(s);
    stack_pop(s);
    v2 = stack_top(s);
    stack_pop(s);
    stack_push(s, v1*v2);
}
 
void stack_dup(Stack s){
    int v = stack_top(s);
    stack_push(s, v);
}
 
void stack_swap(Stack s){
    int v1; int v2;
    v1 = stack_top(s);
    stack_pop(s);
    v2 = stack_top(s);
    stack_pop(s);
    stack_push(s, v1);
    stack_push(s, v2);
}
 
void stack_print(Stack s){
    int v = stack_top(s);
    printf("%i \n", v);
}


//lists 

List newList(){
    List l = malloc(sizeof(struct SList));
    l->head = NULL;
    l->size = 0;
return l;
}
 
void freeList(List l){
    while(l->head != NULL){
        list_removeFirst(l);
    }
    free(l);
}
 
int list_length(List l){
return l->size;
}
 
void list_addFirst(List l, int value){
    Node n = malloc(sizeof(struct SNode));
    n->value = value;
    n->next = l->head;
    l->head = n;
    l->size = l->size + 1;
}
 
void list_addLast(List l, int value){
    Node n = malloc(sizeof(struct SNode));
    n->value = value;
    n->next = NULL;
    if(l->head == NULL){
        l->head = n;
    } else {
        Node cur = l->head;
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = n;
    }
    l->size = l->size + 1;
}
 
int list_get(List l, int index){
    Node cur = l->head;
    int i;
    for(i = 0; i < index; i++){
        cur = cur->next;
    }
return cur->value;
}
 
void list_removeFirst(List l){
    Node n = l->head;
    l->head = n->next;
    free(n);
    l->size = l->size - 1;
}
 
void list_removeValue(List l, int value){
    Node cur = l->head;
    Node prev = NULL;
    while(cur != NULL){
        if(cur->value == value){
            if(prev == NULL){
                l->head = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            l->size = l->size - 1;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}
 
int list_contains(List l, int value){
    Node cur = l->head;
    while(cur != NULL){
        if(cur->value == value) return 1;
        cur = cur->next;
    }
return 0;
}
 
void list_print(List l){
    Node cur = l->head;
    while(cur != NULL){
        printf("%i ", cur->value);
        cur = cur->next;
    }
    printf("\n");
}

//queues

Queue newQueue(){
    Queue q = malloc(sizeof(struct SQueue));
    q->head = 0;
    q->size = 0;
return q;
}
 
void freeQueue(Queue q){
    free(q);
}
 
int queue_isEmpty(Queue q){
return q->size == 0;
}
 
void queue_enqueue(Queue q, int value){
    q->tab[(q->head + q->size) % 100] = value;
    q->size = q->size + 1;
}
 
int queue_front(Queue q){
return q->tab[q->head];
}
 
void queue_dequeue(Queue q){
    q->head = (q->head + 1) % 100;
    q->size = q->size - 1;
}
 
void queue_print(Queue q){
    int i;
    for(i = 0; i < q->size; i++){
        printf("%i ", q->tab[(q->head + i) % 100]);
    }
    printf("\n");
}


//hashtables

Hashtable newHashtable(){
    Hashtable h = malloc(sizeof(struct SHashtable));
    int i;
    for(i = 0; i < HT_SIZE; i++){
        h->tab[i] = NULL;
    }
return h;
}
 
void freeHashtable(Hashtable h){
    int i;
    for(i = 0; i < HT_SIZE; i++){
        Entry cur = h->tab[i];
        while(cur != NULL){
            Entry next = cur->next;
            free(cur);
            cur = next;
        }
    }
    free(h);
}
 
int hashtable_hash(int key){
    int k = key % HT_SIZE;
    if(k < 0) k = k + HT_SIZE;
return k;
}
 
static Entry find(Hashtable h, int key){
    Entry cur = h->tab[hashtable_hash(key)];
    while(cur != NULL){
        if(cur->key == key) return cur;
        cur = cur->next;
    }
return NULL;
}
 
int hashtable_contains(Hashtable h, int key){
return find(h, key) != NULL;
}
 
int hashtable_get(Hashtable h, int key){
    Entry e = find(h, key);
return e->value;
}
 
void hashtable_put(Hashtable h, int key, int value){
    Entry e = find(h, key);
    if(e != NULL){
        e->value = value;
    } else {
        int i = hashtable_hash(key);
        e = malloc(sizeof(struct SEntry));
        e->key = key;
        e->value = value;
        e->next = h->tab[i];
        h->tab[i] = e;
    }
}
 
void hashtable_remove(Hashtable h, int key){
    int i = hashtable_hash(key);
    Entry cur = h->tab[i];
    Entry prev = NULL;
    while(cur != NULL){
        if(cur->key == key){
            if(prev == NULL){
                h->tab[i] = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}
 
void hashtable_print(Hashtable h){
    int i;
    for(i = 0; i < HT_SIZE; i++){
        Entry cur = h->tab[i];
        while(cur != NULL){
            printf("%i -> %i\n", cur->key, cur->value);
            cur = cur->next;
        }
    }
}
