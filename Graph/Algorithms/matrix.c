#include "matrix.h"


int_matrix int_id_n(int n){
	int_matrix id;
	id.m = n;
	id.n = n;
	int **mat = malloc(sizeof(int *)*n);
	for(int i=0;i<n;i++){
		mat[i] = malloc(sizeof(int)*n);
		for(int j=0;j<n;j++){
			if(i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
	id.mat = mat;
	return id;
}

void free_int_matrix(int_matrix a){
	for(int i=0;i<a.m;i++){
		free(a.mat[i]);
	}
	free(a.mat);
	return;
}

void print_int_matrix(int_matrix a){
	for(int i=0;i<a.m;i++){
		for(int j=0;j<a.n;j++){
			printf(" %d ", a.mat[i][j]);
		}
		printf("\n");
	}
	return;
}

int_matrix construct_matrix(){
	int_matrix a;
	int temp;
	printf("Enter the number of rows: ");
	scanf("%d",&temp);
	a.mat = malloc(sizeof(int *)*temp);
	a.m = temp;
	printf("Enter the number of columns: ");
	scanf("%d",&temp);
	a.n = temp;
	printf("Enter each entry seperately, in a left->right then top->down fashion.\n");
	for(int i=0;i<a.m;i++){
		a.mat[i] = malloc(sizeof(int)*a.n);
		for(int j=0;j<a.n;j++){
			scanf("%d", &temp);
			a.mat[i][j] = temp;
		}
	}
	return a;
}

int_matrix multiply(int_matrix a, int_matrix b){
	int_matrix c;
	int **mat;
	if(a.n != b.m)
		return c;
	c.m = a.m;
	c.n = b.n;
	mat = malloc(sizeof(int *)*a.m);
	for(int i=0;i<a.m;i++){
		mat[i] = malloc(sizeof(int)*b.n);
		for(int j=0;j<b.n;j++){
			mat[i][j] = 0;
			for(int k=0;k<a.n;k++){
				mat[i][j] += a.mat[i][k]*b.mat[k][j];
			}
		}
	}
	c.mat = mat;
	return c;
}

int_matrix make_square(int_matrix a, int size){
	int_matrix b;
	if(a.m == 0 || a.n == 0)
		return a;
	if(a.m > size || a.n > size)
		return a;

	b.m = size;
	b.n = size;
	int **mat = malloc(sizeof(int *)*size);
	for(int i=0;i<size;i++){
		mat[i] = malloc(sizeof(int)*size);
		if(i<a.m){
			memcpy(mat[i],a.mat[i],sizeof(int)*a.n);
			for(int j=a.n;j<size;j++){
				mat[i][j] = 0;
			}
		}
		else{
			memset(mat[i],0,sizeof(int)*size);
		}
	}
	b.mat = mat;
	return b;
}

int_matrix multiply_recursive(int_matrix a, int_matrix b){
	long temp[4] = {a.m,a.n,b.m,b.n};
	max_heap(temp,4);
	int size=0;
	temp[1] = temp[0];
	while((temp[1] = temp[1]>>1))
		size++;
	size = 2 << (size-1);

	if(temp[0]>size)
		size = size <<1;

	int_matrix a_padded = make_square(a,size);
	int_matrix b_padded = make_square(b,size);
	int_matrix c;
	if(a.n != b.m)
		return a;
	c.m = b_padded.m;
	c.n = b_padded.m;
	c.mat = malloc(sizeof(int *)*c.m);
	for(int i=0;i<c.m;i++){
		c.mat[i] = malloc(sizeof(int)*c.n);
		for(int j=0;j<c.n;j++){
			c.mat[i][j] = 0;
		}
	}
	multiply_recursive_helper(a_padded,0,size-1,0,size-1,b_padded,0,size-1,0,size-1,&c);
	free_int_matrix(a_padded);
	free_int_matrix(b_padded);
	return c;
}

void multiply_recursive_helper(int_matrix a, int a_rs, int a_re, int a_cs, int a_ce, int_matrix b, int b_rs, int b_re, int b_cs, int b_ce, int_matrix *c){
	//Base case
	if(a_rs==a_re && (a_cs==a_ce && b_cs==b_ce)){
		c->mat[a_rs][b_cs] += a.mat[a_rs][a_cs]*b.mat[b_rs][b_cs];
		return;
	}

	//Midpoints
	int m1, n1, m2, n2;

	m1 = (a_rs+a_re)*.5;
	n1 = (a_cs+a_ce)*.5;
	m2 = (b_rs+b_re)*.5;
	n2 = (b_cs+b_ce)*.5;

	//A_11*B_11
	multiply_recursive_helper(a , a_rs , m1 , a_cs , n1 ,
							  b , b_rs , m2 , b_cs , n2 ,c);
	if(a_cs!=a_ce){
		//A_12*B_21
		multiply_recursive_helper(a , a_rs , m1 , n1+1 , a_ce ,
								  b , m2+1 , b_re , b_cs , n2 ,c);
		if(b_cs!=b_ce){
			//A_11*B_12
			multiply_recursive_helper(a , a_rs , m1 , a_cs , n1 ,
									  b , b_rs , m2 , n2+1 , b_ce ,c);
			//A_12*B_22
			multiply_recursive_helper(a , a_rs , m1 , n1+1 , a_ce ,
									  b , m2+1 , b_re , n2+1 , b_ce ,c);
		}
	}

	if(a_rs!=a_re){
		//A_21*B_11
		multiply_recursive_helper(a , m1+1 , a_re , a_cs , n1 ,
								  b , b_rs , m2 , b_cs , n2 ,c);
		if(b_rs!=b_re){
			//A_22*B_21
			multiply_recursive_helper(a , m1+1 , a_re , n1+1 , a_ce ,
									  b , m2+1 , b_re , b_cs , n2 ,c);
			//A_21*B_12
			multiply_recursive_helper(a , m1+1 , a_re , a_cs , n1 ,
									  b , b_rs , m2 , n2+1 , b_ce ,c);
			//A_22*B_22
			multiply_recursive_helper(a , m1+1 , a_re , n1+1 , a_ce ,
									  b , m2+1 , b_re , n2+1 , b_ce ,c);
		}
	}

	return;
}

int_matrix mult_Strassen(int_matrix a, int_matrix b){
}

char is_Monge(int_matrix a){
	int t1, t2;
	for(int i=0;i<a.m-1;i++){
		for(int j=0;j<a.n-1;j++){
			t1 = a.mat[i][j]+a.mat[i+1][j+1];
			t2 = a.mat[i][j+1]+a.mat[i+1][j];
			if(t1>t2)
				return 0;
		}
	}
	return 1;
}

int *leftmost_min(int_matrix a){
	int c=0;
	int *ret=NULL;
	if(!is_Monge(a))
		return ret;
	ret = malloc(sizeof(int)*a.m);
	for(int i=0;i<a.m;i++){
		for(int j=c;j<a.n;j++){
			if(a.mat[i][j]<a.mat[i][c]){
				c=j;
			}
		}
		ret[i] = a.mat[i][c];
	}
	return ret;
}