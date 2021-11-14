#include <limits.h>
#include "stack_fifo.h"

/* Contains declarations of the combinatorial logic */

typedef struct set_partition{
	unsigned int **parts;
	unsigned int n;
} set_partition;

/* Returns n! if n<13, and 0 otherwise. */
unsigned int factorial(unsigned int n);

/* Generates identity map (array) of the n element set. Knowledge of the size n belongs to the caller. */
unsigned int *i_n(unsigned int n);

/* Composition f(g). "o" is similar to \circ. Assumed that g[i]<n_f for all i<n_g */
unsigned int *fog(unsigned int *f, unsigned int *g, unsigned int n_f, unsigned int n_g);

/* 
Returns array of all permutations of the n element set.
IMPORTANT: Due to limitations on unsigned int, returns NULL if n>12.
IMPORTANT: Very memory intensive; n>7 is not recommended.
*/
unsigned int **get_all_permutations(unsigned int n);
void free_all_permutations(unsigned int **permutations, unsigned int n);
void print_all_permutations(unsigned int n);