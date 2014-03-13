#ifndef _LIST_H
#define _LIST_H

typedef struct node {
	 void *pdata;
	 struct node *next;
} node, *pnode, **ppnode;

typedef int (*listcompare)(void *first, void *second);
typedef void (*listshow)(void *data);

typedef struct list {
	 pnode head;
	 listcompare compare;
	 listshow show;
}*plist;

plist list_init(listcompare compare,
				listshow show);
int list_empty(plist pt);
void list_destory(plist pt);
void list_display(plist pt);
void list_qsort(plist pt);
void list_insert(plist pt, void *pdata);
pnode list_search(plist pt, void* data);


#endif


















