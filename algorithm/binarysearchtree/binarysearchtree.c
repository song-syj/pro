#include<stdio.h>
#include<stdlib.h>
#include"binarysearchtree.h"

Link MakeNode(Type z)
{
	Link p=(Link)malloc(sizeof *p);
	p->parent=p->left=p->right=NULL;
	p->item=z;
	return p;
}
void FreeNode(Link p)
{
	free(p);
}

void InorderTreeWalk(Link t,void (*Visit)(Link))
{
	if(t==NULL)
		return;
	InorderTreeWalk(t->left,Visit);
	Visit(t);
	InorderTreeWalk(t->right,Visit);
}
void PreorderTreeWalk(Link t,void (*Visit)(Link))
{
	if(t==NULL)
		return;
	Visit(t);
	PreorderTreeWalk(t->left,Visit);
	PreorderTreeWalk(t->right,Visit);
}
void PostorderTreeWalk(Link t,void (*Visit)(Link))
{
	if(t==NULL)
		return;
	PostorderTreeWalk(t->left,Visit);
	PostorderTreeWalk(t->right,Visit);
	Visit(t);
}


Link TreeSearch(Link t,Type k)
{
	while(t!=NULL&&t->item!=k)
	{
		if(k<t->item)
			t=t->left;
		else
			t=t->right;
	}
	return t;
}
Link TreeMinimum(Link t)
{
	if(t==NULL)
		return t;
	while(t->left!=NULL)
	{
		t=t->left;
	}
	return t;
}
Link TreeMaximum(Link t)
{
	if(t==NULL)
		return t;
	while(t->right!=NULL)
	{
		t=t->right;
	}
	return t;
}
Link TreeSuccessor(Link x)
{
	if(x->right!=NULL)
	{
		return TreeMinimum(x->right);
	}
	else
	{
		while(x->parent!=NULL&&x->parent->left!=x)
		{
			x=x->parent;
		}
		return x->parent;
	}
}
Link TreePredecessor(Link x)
{
	if(x->left!=NULL)
	{
		return TreeMaximum(x->left);
	}
	else
	{
		while(x->parent!=NULL&&x->parent->right!=x)
		{
			x=x->parent;
		}
		return x->parent;
	}
}
void TreeInsert(Link* t,Link z)
{
	Link x,y;
	y=NULL;
	x=*t;
	while(x!=NULL)
	{
		y=x;
		if(x->item>z->item)
			x=x->left;
		else
			x=x->right;
	}
	z->parent=y;
	if(y==NULL)
		*t=z;
	else if(y->item>z->item)
		y->left=z;
	else
		y->right=z;
}
static void Transplant(Link* t,Link x,Link y)
{
	if(x->parent==NULL)
		*t=y;
	else if(x->parent->left==x)
		x->parent->left=y;
	else 
		x->parent->right=y;
	if(y!=NULL)
		y->parent=x->parent;

}
void TreeDelete(Link* t,Link z)
{
	Link y;
	if(z->left==NULL)
		Transplant(t,z,z->right);
	else if(z->right==NULL)
		Transplant(t,z,z->left);
	else
	{
		y=TreeMinimum(z->right);	
		if(z->right!=y)
		{
			Transplant(t,y,y->right);
			y->right=z->right;
			y->right->parent=y;
		}
		Transplant(t,z,y);
		y->left=z->left;
		y->left->parent=y;
	}
}
