#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#define Type unsigned char
typedef struct node* Link;
struct node {
	Type item ;
	Link left ,right,parent;
};

void InorderTreeWalk(Link t,void (*Visit)(Link));
void PreorderTreeWalk(Link t,void (*Visit)(Link));
void PostorderTreeWalk(Link t,void (*Visit)(Link));
Link MakeNode(Type z);
void FreeNode(Link p);
Link TreeSearch(Link t,Type k);
Link TreeMinimum(Link t);
Link TreeMaximum(Link t);
Link TreeSuccessor(Link x);
Link TreePredecessor(Link x);
void TreeInsert(Link* t,Link z);
void TreeDelete(Link* t,Link z);

#endif
