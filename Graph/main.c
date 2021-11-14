#include "graph2_r.h"

int main(int argc, char **argv){
	graph1 *g = n_complete1(10);
	graph2_r *h = graph2_r_from_graph1(*g);

	unsigned int len=0;
	vertex_r *path = shortest_path2_r(*h,0,9,&len);
	/*
	for(unsigned int i=0;i<len;i++){
		printf(" %d", path[i].v_id);
	}
	printf("\n");
	*/

	//free(path);
	delete_graph1(g);
	delete_graph2_r(h);
	return 0;
}