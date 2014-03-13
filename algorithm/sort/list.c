#include<stdlib.h>
#include<stdio.h>
#include"list.h"

plist list_init(listcompare compare,
				listshow show)
{
	 plist pt;
	 
	 pt = (plist)malloc(sizeof(*pt));
	 if(!pt) {
		  printf("create list fail!\n");
		  exit(0);
	 }

	 pt->head = NULL;
	 pt->compare = compare;
	 pt->show = show;

	 return pt;
}

int list_empty(plist pt)
{
	 return (pt->head == NULL);
}


void list_insert(plist pt, void *pdata )
{
	 pnode newnode;
	 
	 newnode = (pnode)malloc(sizeof(*newnode));
	 if(!newnode) {
		  printf("malloc fail!\n");
		  return;
	 }
	 
	 newnode->pdata = pdata;
	 
	 newnode->next = pt->head;
	 pt->head = newnode;
}

pnode list_search(plist pt, void* data)
{
	 pnode pn;
	 pn = pt->head;
	 
	 while(pn) {
		  if(!pt->compare(pn->pdata, data))
			   break;
		  pn = pn->next;
	 }

	 return pn;
}

void list_destory(plist pt)
{
	 pnode pn;
	 pnode tmp;
	 pn = pt->head;
	 
	 while(pn) {
		  tmp = pn;
		  pn = pn->next;
		  free(tmp);
	 }
	 
	 if(pt)
		  free(pt);
}

void list_display(plist pt)
{
	 pnode pn;
	 pn = pt->head;
	 
	 while(pn) {
		  pt->show(pn->pdata);
		  pn = pn->next;
	 }
	 putchar('\n');
}

/* static void */
/* quicksort(ppnode pphead, pnode ptail, listcompare compare) */
/* { */
/* 	 ppnode left_walk, right_walk; */
/* 	 pnode right, old, piovt; */
/* 	 int left_count, right_count, count; */
	 
/* 	 if(pphead == NULL || *pphead == ptail) */
/* 		  return; */

/* 	 do { */
/* 		  piovt = *pphead; */
/* 		  left_walk = pphead; */
/* 		  right_walk = &right; */
/* 		  left_count = right_count = 0; */
		  
/* 		  for(old = (*pphead)->next; old != ptail; old = old->next) { */
/* 			   if(compare(old->pdata, piovt->pdata) < 0) { */
/* 					left_count++; */
/* 					*left_walk = old; */
/* 					left_walk = &(old->next); */
/* 			   } else { */
/* 					right_count++; */
/* 					*right_walk = old; */
/* 					right_walk = &(old->next); */
/* 			   } */
/* 		  } */

/* 		  *right_walk = ptail; */
/* 		  *left_walk = piovt; */
/* 		  piovt->next = right; */

/* 		  if (left_count < right_count) { */
/* 			   quicksort(pphead, piovt, compare); */
/* 			   pphead = &(piovt->next); */
/* 			   count = right_count; */
/* 		  } else { */
/* 			   quicksort(&(piovt->next), ptail, compare); */
/* 			   ptail = piovt; */
/* 			   count = left_count; */
/* 		  } */
		  
/* 	 } while(count > 1); */
	 
/* } */


static
void lqsort(pnode head, pnode tail, listcompare compare)
{
	 void *data;
	 pnode pivot, left_walk, right_walk, old;

	 if(head == NULL
		|| head == tail
		|| head->next == tail)
		  return;
		  
	 pivot = head->next;
	 data = pivot->pdata;
	 left_walk = head;
	 right_walk = pivot;
	 
	 for(old = head->next->next;
		 old != tail; old = old->next) {
		  if(compare(old->pdata, data) < 0) {
			   left_walk = left_walk->next = old;
		  } else {
			   right_walk = right_walk->next = old;
		  }
	 }

	 left_walk->next = pivot;
	 right_walk->next = tail;

	 lqsort(pivot, tail, compare);
	 lqsort(head, pivot, compare);
}

void list_qsort(plist pt)
{
	 node hnod;
	 //quicksort(&(pt->head), NULL, pt->compare);
	 hnod.next = pt->head;
	 lqsort(&hnod, NULL, pt->compare);
	 pt->head = hnod.next;
}



















