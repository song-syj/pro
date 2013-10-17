#include<stdio.h>
#include"rbtree_augment.h"

int compare(void* x, void* y);
void visit(rbnode *node);
int 
main(int argc, char* argv[])
{
	int key[] = {26,17,41,14,21,30,47,10,16,19,23,28,38,7,12,15,20,35,39,3};
	int data[20];
	int i;
	rbtree* ptr_tree = rbtree_create(compare, visit);

	for(i=0;i<20;i++) {
		data[i] = i;
		rbtree_insert(ptr_tree,(void *)(key+i),(void *)(data+i));
	}

/*	printf("The preorder of the redblacktree : \n");
	rbtree_preorder_walk(ptr_tree,ptr_tree->root);
	printf("The inorder of the redblacktree : \n");
	rbtree_inorder_walk(ptr_tree,ptr_tree->root);*/

//	printf("After delet 21: \n");
//	rbtree_delete(ptr_tree,key+6);
	rbtree_display(ptr_tree);

	for(i = 0; i< 20; i++) {
		printf("(%d, %d) ",i+1 , *(int *)(os_select(ptr_tree->root, i+1)->key));
	}
	putchar('\n');

	printf("The inorder of the redblacktree : \n");
	rbtree_inorder_walk(ptr_tree,ptr_tree->root);

	for(i = 0; i< 20; i++) {
		printf("(%d, %d) ", os_rank(ptr_tree, rbtree_search(ptr_tree, key+i)),key[i]);
	}
	putchar('\n');
	//printf("The preorder of the redblacktree : \n");
	//rbtree_preorder_walk(ptr_tree,ptr_tree->root);
	/*printf("The inorder of the redblacktree : \n");
	rbtree_inorder_walk(ptr_tree,ptr_tree->root);
	rbtree_destroy(ptr_tree,ptr_tree->root);*/

	return 0;
}

int 
compare(void *x, void *y)
{
	if(*(int *)x == *(int *)y)
		return 0;
	else if(*(int *)x > *(int *)y)
		return 1;
	else
		return -1;
 
}

void
visit(rbnode *node)
{
	printf("node->key: %d ",*(int *)(node->key));
	printf("node->data: %d ",*(int *)(node->data));
	if(node->color == RED)
		printf("node->color: RED\n");
	else
		printf("node->color: BLACK\n");
}
