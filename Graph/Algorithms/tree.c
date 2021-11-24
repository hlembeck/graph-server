#include "tree.h"

tree_node *get_root(tree_node *node){
	tree_node *root = node;
	while(root->parent){
		root = root->parent;
	}
	return node;
}

int max_children(tree_node *node){
	int temp, max = 0;
	tree_node *root = get_root(node);
	fifo *q = init_fifo(root);
	while(q){
		root = deq(&q)->left_child;
		temp=1;
		enq(q,root);
		while((root=root->right_sibling)){
			temp++;
			enq(q,root);
		}
		if(max<temp)
			max=temp;
	}
	return max;
}