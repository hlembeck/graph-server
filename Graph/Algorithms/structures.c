#include "structures.h"

char *pop(stack **s){
	if(*s){
		stack *t = *s;
		char *ret = (*s)->value;
		*s = (*s)->next;
		free(t);
		return ret;
	}
	return NULL;
}

void push(stack **s, char *value){
	stack *top = malloc(sizeof(stack));
	top->value = value;
	top->next = *s;
	*s=top;
	return;
}

stack *init_stack(char *value){
	stack *ret = malloc(sizeof(stack));
	ret->value = value;
	ret->next = NULL;
	return ret;
}

void free_stack(stack *s){
	while(s){
		pop(&s);
	}
	return;
}

void print_stack(stack *s){
	printf("\n\n---- Print of stack ----\n\n");
	while(s->next){
		printf("'%p'\n", s->value);
		s=s->next;
	}
	printf("\n------------------------\n\n");
	return;
}



fifo *init_fifo(char *value){
	fifo *ret = malloc(sizeof(fifo));
	ret->value = value;
	ret->next = NULL;
	ret->tail = ret;
	return ret;
}

void enq(fifo *q, char *value){
	fifo *tail = malloc(sizeof(fifo));
	tail->value = value;
	tail->next = NULL;
	tail->tail = tail;
	(q->tail)->next = tail;
	q->tail = tail;
	return;
}

char *deq(fifo **q){
	if(*q){
		char *ret = (*q)->value;
		fifo *t = *q;
		*q = (*q)->next;
		free(t);
		return ret;
	}
	return NULL;
}

void free_fifo(fifo *q){
	while(q){
		deq(&q);
	}
	return;
}

sll *init_sll(){
	dll *list = malloc(sizeof(dll));
	list.nil = malloc(sizeof(dll_node));
	nil->np = 0;
}

void insert_sll(sll *list, int key){
	dll_node *node = malloc(sizeof(dll_node));
	node->key = key;
	node->np = list->nil->np;
	list->nil->np = node;
	return;
}