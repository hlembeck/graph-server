#include "stack_fifo.h"

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
	printf("bp1\n");
	(q->tail)->next = tail;
	printf("bp2\n");
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