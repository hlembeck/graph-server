#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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