#ifndef _RB_TREE_H
#define _RB_TREE_H

#define True 1
#define False 0
#define Bool char

typedef enum rbcolor{BLACK,RED} rbcolor;

typedef struct rbnode{
	void *key;
	void *data;
	void max;

	struct rbnode *left;
	struct rbnode *right;
	struct rbnode *parent;

	rbcolor color;
}rbnode;

typedef int (*rbtree_compare)(void *, void *);
typedef void (*rbtree_visit)(rbnode *);

typedef struct rbtree{
	rbnode *root;
	rbnode *nil;
	rbtree_compare compare;
	rbtree_visit visit;

}rbtree;

rbtree * rbtree_create(rbtree_compare compare, rbtree_visit visit);
void rbtree_destroy(rbtree *tree, rbnode *node);

rbnode * rbtree_search(rbtree *tree, void *key);
void rbtree_inorder_walk(rbtree *tree, rbnode *node);
void rbtree_preorder_walk(rbtree *tree, rbnode *node);

void rbtree_insert(rbtree *tree, void *key, void *data);
Bool rbtree_delete(rbtree *tree, void *key);

rbnode * new_rbnode(void);
void delete_rbnode(rbnode *node);
rbtree * new_rbtree(void);

#endif
