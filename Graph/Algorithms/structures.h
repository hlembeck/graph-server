#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

typedef struct tree_node{
	struct tree_node *parent;
	struct tree_node *left_child;
	struct tree_node *right_sibling;
} tree_node;

typedef struct int_matrix{
	int **mat;
	int m;
	int n;
}int_matrix;

typedef struct stack{
	char *value;
	struct stack *next;
} stack;

char *pop(stack **s);
void push(stack **s, char *value);
stack *init_stack(char *value);
void free_stack(stack *s);
void print_stack(stack *s);



typedef struct fifo{
	char *value;
	struct fifo *next, *tail;
} fifo;

fifo *init_fifo(char *value);
void enq(fifo *q, char *value);
char *deq(fifo **q);
void free_fifo(fifo *q);


typedef struct dll_node{
	int key;
	struct dll_node *np;
} dll_node;

typedef struct dll{
	dll_node *nil;
} dll;

dll *init_dll();
//Inserts after prev
void insert_dll(dll *list, int key);
ll_node *find_node(dll *list, int key);