#include<stdio.h>
#include<stdlib.h>
#include"binarysearchtree.h"

void print_node(Link p)
{
	printf("%4d",p->item);
}

int main(void)
{
	unsigned char data[]={15,18,6,7,13,3,4,20,9,17,2};
	Link root=NULL;
	Link pnode;
	Link s;
	int i;
	for(i=0;i<11;i++)
	{
		pnode=MakeNode(data[i]);
		TreeInsert(&root,pnode);
	}
	printf("The preorder  is :");
	PreorderTreeWalk(root,print_node);
	putchar('\n');
	printf("The inorder   is :");
	InorderTreeWalk(root,print_node);
	putchar('\n');
	printf("The postorder is :");
	PostorderTreeWalk(root,print_node);
	putchar('\n');
	printf("the max of the tree is:");
	print_node(TreeMaximum(root));
	putchar('\n');
	printf("the min of the tree is:");
	print_node(TreeMinimum(root));
	putchar('\n');
	s=TreeSearch(root,15);
	printf("The result of search is :%4d\n",s->item);
	printf("The predecessor of 15 is:%4d\n",TreePredecessor(s)->item);
	printf("The successor   of 15 is:%4d\n",TreeSuccessor(s)->item);
	TreeDelete(&root,s);
	free(s);
	printf("After delete 15 :\n");
	InorderTreeWalk(root,print_node);
	putchar('\n');
	PreorderTreeWalk(root,print_node);
	putchar('\n');
	return 0;
}
