#include "matrix.h"

int main(){
	int_matrix a = construct_matrix();
	int *list;
	print_int_matrix(a);
	if(is_Monge(a)){
		list = leftmost_min(a);
		for(int i=0;i<a.m;i++){
			printf("%d , ", list[i]);
		}
		printf("\n");
		free(list);
	}
	free_int_matrix(a);
	return 0;
}