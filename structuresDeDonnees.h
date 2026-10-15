#ifndef STRUCTURESDEDONNEES_H
#define STRUCTURESDEDONNEES_H


//array 

struct SArray {
int tab[100];
int size;
};
 
typedef struct SArray *Array;
 
Array newArray();
void freeArray(Array a);
int  array_length(Array a);
int  array_get(Array a, int index);
void array_set(Array a, int index, int value);
void array_append(Array a, int value);
void array_insertAt(Array a, int index, int value);
void array_removeAt(Array a, int index);
int  array_indexOf(Array a, int value);
void array_print(Array a);

//stacks

struct SStack {
int tab[100];
int ptr;
};
 
typedef struct SStack *Stack;
 
Stack newStack();
void freeStack(Stack s);
void stack_push(Stack s, int value);
int  stack_top(Stack s);
void stack_pop(Stack s);
void stack_add(Stack s);
void stack_sub(Stack s);
void stack_mult(Stack s);
void stack_dup(Stack s);
void stack_swap(Stack s);
void stack_print(Stack s);

//lists

struct SNode {
int value;
struct SNode *next;
};
 
typedef struct SNode *Node;
 
struct SList {
Node head;
int size;
};
 
typedef struct SList *List;
 
List newList();
void freeList(List l);
int  list_length(List l);
void list_addFirst(List l, int value);
void list_addLast(List l, int value);
int  list_get(List l, int index);
void list_removeFirst(List l);
void list_removeValue(List l, int value);
int  list_contains(List l, int value);
void list_print(List l);


//queues 

 
struct SQueue {
int tab[100];
int head;
int size;
};
 
typedef struct SQueue *Queue;
 
Queue newQueue();
void freeQueue(Queue q);
int  queue_isEmpty(Queue q);
void queue_enqueue(Queue q, int value);
int  queue_front(Queue q);
void queue_dequeue(Queue q);
void queue_print(Queue q);

//hashtables

#define HT_SIZE 100
 
struct SEntry {
int key;
int value;
struct SEntry *next;
};
 
typedef struct SEntry *Entry;
 
struct SHashtable {
Entry tab[HT_SIZE];
};
 
typedef struct SHashtable *Hashtable;
 
Hashtable newHashtable();
void freeHashtable(Hashtable h);
int  hashtable_hash(int key);
int  hashtable_contains(Hashtable h, int key);
int  hashtable_get(Hashtable h, int key);
void hashtable_put(Hashtable h, int key, int value);
void hashtable_remove(Hashtable h, int key);
void hashtable_print(Hashtable h);



#endif 
