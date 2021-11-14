#include "combinatorics.h"

unsigned int factorial(unsigned int n){
	if(n>12)
		return 0;
	if(n==0)
		return 1;
	return factorial(n-1)*n;
}

unsigned int *i_n(unsigned int n){
	unsigned int *id = malloc(sizeof(unsigned int)*n);
	for(unsigned int i=0;i<n;i++){
		id[i]=i;
	}
	return id;
}

unsigned int *fog(unsigned int *f, unsigned int *g, unsigned int n_f, unsigned int n_g){
	unsigned int *comp = malloc(sizeof(unsigned int)*n_g);
	for(unsigned int i=0;i<n_g;i++){
		comp[i] = f[g[i]];
	}
	return comp;
}

unsigned int **get_all_permutations(unsigned int n){
	if(n==0 || n>12)
		return NULL;
	unsigned int smallFactorial = factorial(n-1);
	//printf("\n(n-1)! = %d\n", smallFactorial);
	unsigned int **result = malloc(sizeof(char *)*n*smallFactorial);
	if(n==1){
		result[0] = i_n(1);
		return result;
	}
	unsigned int **smallResult = get_all_permutations(n-1);
	unsigned int c = 0;
	for(unsigned int i=0;i<n;i++){
		for(unsigned int j=0;j<smallFactorial;j++){
			unsigned int *permutation = malloc(sizeof(unsigned int)*n);
			permutation[0] = i;
			//printf("Current permutation has position 0 set to %d\n", i);
			for(unsigned int k=0;k<n-1;k++){
				if(smallResult[j][k]==i){
					permutation[k+1] = n-1;
					continue;
				}
				permutation[k+1] = smallResult[j][k];
				//printf("Current permutation has position %d set to %d\n", k+1, permutation[k+1]);
			}
			result[c] = permutation;
			c++;
		}
	}

	for(unsigned int i=0;i<smallFactorial;i++){
		free(smallResult[i]);
	}
	free(smallResult);
	return result;
}

void free_all_permutations(unsigned int **permutations, unsigned int n){
	for(unsigned int i=0;i<factorial(n);i++){
		free(permutations[i]);
	}
	free(permutations);
	return;
}

void print_all_permutations(unsigned int n){
	unsigned int **permutations = get_all_permutations(n);
	printf("\n------ Printing all permutations of the %d element set ------\n", n);
	for(unsigned int i=0;i<factorial(n);i++){
		printf("\nPermutation %d: \n", i);
		for(unsigned int j=0;j<n;j++){
			printf("  %d -> %d\n", j, permutations[i][j]);
		}
	}
	printf("\n-------------------------------------------------------------\n");
	free_all_permutations(permutations, n);
	return;
}