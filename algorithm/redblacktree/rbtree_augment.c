#include"rbtree_augment.h"
#include<stdio.h>
#include<stdlib.h>

#define MAXSTACKSIZE 100
static rbnode *stack[MAXSTACKSIZE];
static int top = 0;


rbtree * rbtree_create(rbtree_compare compare, rbtree_visit visit);
void rbtree_destroy(rbtree *tree, rbnode *node);
void rbtree_display(rbtree *tree);

rbnode * rbtree_search(rbtree *tree, void *key);
void rbtree_inorder_walk(rbtree *tree, rbnode *node);
void rbtree_preorder_walk(rbtree *tree, rbnode *node);

void rbtree_insert(rbtree *tree, void *key, void *data);
Bool rbtree_delete(rbtree *tree, void *key);

rbnode * os_select(rbnode *x, int i);
int os_rank(rbtree *tree, rbnode *x);

rbnode * new_rbnode(void);
void delete_rbnode(rbnode *node);
rbtree * new_rbtree(void);

static void rbtree_transplant(rbtree *tree, rbnode *u, rbnode *v);
static void rbtree_insert_fixup(rbtree *tree, rbnode *z);
static void rbtree_delete_fixup(rbtree *tree, rbnode *x);

static void rotate_left(rbtree *tree, rbnode *x);
static void rotate_right(rbtree *tree, rbnode *x);

static rbnode * rbtree_successor(rbtree *tree, rbnode *x);
static rbnode * rbtree_predecessor(rbtree *tree, rbnode *x);
static rbnode * rbtree_max(rbtree *tree, rbnode *x);
static rbnode * rbtree_min(rbtree *tree, rbnode *x);

rbtree *
rbtree_create(rbtree_compare compare, rbtree_visit visit)
{
	//rbtree *tree = (rbtree *)malloc(sizeof(rbtree));
	//tree->nil = (rbnode *)malloc(sizeof(rbnode));
	rbtree *tree = new_rbtree();
	tree->nil = new_rbnode();
	tree->nil->left = tree->nil->right = tree->nil->parent = tree->nil;
	tree->nil->color = BLACK;
	tree->nil->size = 0;

	tree->root = tree->nil;
	tree->compare = compare;
	tree->visit = visit;
	
	return tree;
}

void
rbtree_destroy(rbtree *tree, rbnode *node)
{
	if(node == tree->nil)
		return;
	rbtree_destroy(tree,node->left);
	rbtree_destroy(tree,node->right);
	delete_rbnode(node);
}

void
rbtree_display(rbtree *tree)
{
	rbnode *p;
	int i, t,width,widthMax; 
	width = 7;
	widthMax = 60;
	t = width;
	if(tree->root == tree->nil) {
		printf("Empty redblack tree!\n");
		return ;
	}
	stack[++top] = tree->root;
	while(top > 0) {
		p = stack[top--];
		for(i=0; i < t; i++)
			putchar(' ');
		if(p == NULL) {
			putchar(')');
			for(i = t-6; i < widthMax; i++)
				putchar('-');
		    putchar('\n');
			t -= width;
			continue;
		} else {
			if(p == tree->nil)
				printf(" NIL,0");
			else {
				printf("(%2d",*(int*)(p->key));
				if(p->color == RED)
					printf("R");
				else
					printf("B");
				printf(",%2d",p->size);
			}
		}
		for(i = t; i < widthMax; i++)
			putchar('-');
		putchar('\n');
		if(p->left != tree->nil ||
				p->right != tree->nil) {
			stack[++top] = NULL;
			stack[++top] = p->right;
			stack[++top] = p->left;
			t += width;
		}
	}

}

rbnode *
rbtree_search(rbtree *tree, void *key)
{
	rbnode *x = tree->root;
	while(x != tree->nil) {
		int cmp = tree->compare(x->key, key);
		if(cmp == 0) {
			break;
		} else if(cmp==1) {
			x = x->left;	
		} else {
			x = x->right;
		}
	}

	return x;
}

void 
rbtree_inorder_walk(rbtree *tree, rbnode *node)
{
	if(node == tree->nil)
		return;
	rbtree_inorder_walk(tree, node->left);
	tree->visit(node);
	rbtree_inorder_walk(tree, node->right);
}

void 
rbtree_preorder_walk(rbtree *tree, rbnode *node)
{
	if(node == tree->nil)
		return;
	tree->visit(node);
	rbtree_preorder_walk(tree, node->left);
	rbtree_preorder_walk(tree, node->right);
}

void
rbtree_postorder_walk(rbtree *tree, rbnode *node)
{
	if(node == tree->nil)
		return;
	rbtree_postorder_walk(tree, node->left);
	rbtree_postorder_walk(tree, node->right);
	tree->visit(node);
}

void
rbtree_insert(rbtree *tree, void *key, void *data)
{
	rbnode *x, *y, *z ;
	int cmp;

	z = new_rbnode(); 
	z->color = RED;
	z->left = z->right = tree->nil;
	z->key = key;
	z->data = data;
	z->size = 1;
	
	x = tree->root;
	y = tree->nil;
	while(x != tree->nil) {
		y = x;
		cmp = tree->compare(x->key, key);
		if(cmp == 0) {
			break;
		} else if(cmp == 1) {
			x = x->left;	
		} else {
			x = x->right;
		}
	}
	
	z->parent = y;
	if(y == tree->nil)
		tree->root = z;
	else if(cmp > 0)
		y->left = z;
	else 
		y->right = z;
		
	while(y != tree->nil) {
		y->size++;
		y = y->parent;
	}

	rbtree_insert_fixup(tree, z);
}

Bool 
rbtree_delete(rbtree *tree, void *key)
{
	rbnode *x,*y,*z;
	rbcolor original_color;
	z = rbtree_search(tree,key);
	if(z == tree->nil)
		return False;
	y=z;
	original_color = y->color;

	if(z->left == tree->nil) {
		x = z->right;
		rbtree_transplant(tree, z, z->right);
	} else if(z->right == tree->nil) {
		x = z->left;
		rbtree_transplant(tree, z, z->left);
	} else {
		y = rbtree_min(tree,z->right);
		original_color = y->color;
		x = y->right;
		if(y->parent == z)
			x->parent = y;
		else {
			rbtree_transplant(tree, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		rbtree_transplant(tree, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
		y->size = z->size;
	}
	delete_rbnode(z);

	y = x->parent;
	while(y != tree->nil)
	{
		y->size --;
		y = y->parent;
	}

	if(original_color == BLACK)
		rbtree_delete_fixup(tree,x);

	return True;
}

rbnode *
os_select(rbnode *x, int i)
{
	int r = x->left->size + 1;
	if(r == i)
		return x;
	else if(r > i) 
		return os_select(x->left, i);
	else
		return os_select(x->right, i-r);
}

int
os_rank(rbtree *tree, rbnode *x)
{
	rbnode *y;
	int r;
	r = x->left->size + 1;
	while(x != tree->root) {
		if(x == x->parent->right) 
			r = r + x->parent->left->size + 1;
		x = x->parent;
	}
	return r;

}


static void 
rbtree_transplant(rbtree *tree, rbnode *u, rbnode *v)
{
	if(u->parent == tree->nil)
		tree->root = v;
	else if(u == u->parent->left)
		u->parent->left = v;
	else 
		u->parent->right = v;

	v->parent = u->parent;
}

static void
rbtree_insert_fixup(rbtree *tree, rbnode *z)
{
	rbnode *y;
	while(z->parent->color == RED) {
		if(z->parent == z->parent->parent->left) {
			y =  z->parent->parent->right;//uncle
			if(y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color =RED;
				z=z->parent->parent;
			} else {
				if(z == z->parent->right) {
					z = z->parent;
					rotate_left(tree,z);
				}
				z->parent->color =  BLACK;
				z->parent->parent->color = RED;
				rotate_right(tree,z->parent->parent);
			}
		} else {
			y = z->parent->parent->left;
			if(y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color =RED;
				z=z->parent->parent;
			} else {
				if(z == z->parent->left) {
					z = z->parent;
					rotate_right(tree,z);
				}
				z->parent->color =  BLACK;
				z->parent->parent->color = RED;
				rotate_left(tree,z->parent->parent);
			}
		}
	}
	tree->root->color = BLACK ;
}

static void 
rbtree_delete_fixup(rbtree *tree, rbnode *x)
{
	rbnode *w;
	while(x != tree->root &&
			x->color == BLACK) {
		if(x == x->parent->left) {
			w = x->parent->right;
			if(w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotate_left(tree,x->parent);
				w = x->parent->right;
			} else if(w->left->color == BLACK &&
						w->right->color ==BLACK) {
					w->color = RED;
					x = x->parent;
			} else {
				if(w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color =RED;
					rotate_right(tree,w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				rotate_left(tree,x->parent);
				x = tree->root;
			}
			
		} else {
			w = x->parent->left;
			if(w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotate_right(tree,x->parent);
				w = x->parent->left;
			} else if(w->right->color == BLACK &&
						w->left->color ==BLACK) {
					w->color = RED;
					x = x->parent;
			} else {
				if(w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color =RED;
					rotate_left(tree,w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rotate_right(tree,x->parent);
				x = tree->root;
			}

		}
	}
	x->color = BLACK;
}
static void
rotate_left(rbtree *tree, rbnode *x)
{
	rbnode *y = x->right;

	x->right = y->left;
	if(y->left != tree->nil) {
		y->left->parent=x;
	}

	y->parent = x->parent;
	if(x->parent == tree->nil) {
		tree->root = y;
	} else if(x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	y->left = x;
	x->parent =  y;

	y->size = x->size;
	x->size = x->right->size + x ->left->size + 1;

}

static void 
rotate_right(rbtree *tree, rbnode *x)
{
	rbnode *y = x->left;

	x->left = y->right;
	if(y->right != tree->nil) {
		y->right->parent = x;
	}
	
	y->parent = x->parent;
	if(x->parent == tree->nil) {
		tree->root = y;
	} else if(x == x->parent->right) {
		x->parent->right = y;
	} else {
		x->parent->left =  y;
	}

	x->parent = y;
	y->right = x;

	y->size = x->size;
	x->size = x->right->size + x ->left->size + 1;
}

static rbnode *
rbtree_successor(rbtree *tree, rbnode *x)
{
	if(x->right != tree->nil) {
		return rbtree_min(tree, x->right);
	} else {
		while(x->parent != tree->nil &&
				x->parent->right == x) {
			x = x->parent;
		}
		return x->parent ;
	}
}

static rbnode *
rbtree_predecessor(rbtree *tree, rbnode *x)
{
	if(x->left != tree->nil) {
		return rbtree_max(tree, x->left);
	} else {
		while(x->parent != tree->nil &&
				x->parent->left == x) {
			x = x->parent;
		}
		return x->parent ;
	}
}

static rbnode *
rbtree_max(rbtree *tree, rbnode *x)
{
	while(x->right != tree->nil) {
		x = x->right;
	}
	
	return x;
}

static rbnode *
rbtree_min(rbtree *tree, rbnode *x)
{
	while(x->left != tree->nil) {
		x = x->left;
	}
	
	return x;
}

rbnode *
new_rbnode(void)
{
	rbnode *node = (rbnode *)malloc(sizeof(rbnode));
	if(node == NULL) {
		perror("alloc new rbnode");
		exit(1);
	}
	return node;
}

void
delete_rbnode(rbnode *node)
{
	free(node);
}

rbtree *
new_rbtree(void)
{
	rbtree *tree = (rbtree *)malloc(sizeof(rbnode));
	if(tree == NULL) {
		perror("alloc new rbtree");
		exit(1);
	}
	return tree;
}
