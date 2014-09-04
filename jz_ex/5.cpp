#include<iostream>
#include<stack>

using namespace std;

struct ListNode
{
	int m_nValue;
	ListNode *m_pNext;
};

void PrintListReversingly(ListNode *pHead)
{
	if(pHead == NULL) return;

	ListNode *pNode = pHead;
	stack<ListNode *> nodes;
	while(pNode != NULL) {
		nodes.push(pNode);
		pNode = pNode->m_pNext;
	}

	while(!nodes.empty()) {
		pNode = nodes.top();
		printf("%d ", pNode->m_nValue);
		nodes.pop();
	}
	printf("\n");
}

void AddToTailListNode(ListNode **pHead, int value)
{
	if(pHead == NULL)
		return;

	ListNode *pNew = new ListNode;
	pNew->m_pNext = NULL;
	pNew->m_nValue = value;

	if(*pHead == NULL) {
		*pHead = pNew;
	} else {
		ListNode *pNode = *pHead;
		while(pNode->m_pNext != NULL) {
			pNode = pNode->m_pNext;
		}

		pNode->m_pNext = pNew;
	}
}

void RemoveListNode(ListNode **pHead, int value) 
{
	if(pHead == NULL || *pHead == NULL) return; 

	ListNode *pToBeDeleted = NULL;
	if((*pHead)->m_nValue == value) {
		pToBeDeleted = *pHead;
		*pHead = (*pHead)->m_pNext;
	} else {
		ListNode *pNode = *pHead;
		while(pNode->m_pNext != NULL 
				&& pNode->m_pNext->m_nValue != value) {
			pNode = pNode->m_pNext;
		}

		if (pNode->m_pNext != NULL) {
			pToBeDeleted = pNode->m_pNext;
			pNode->m_pNext = pNode->m_pNext->m_pNext;
		}
	}

	if(pToBeDeleted != NULL) {
		delete pToBeDeleted;
		pToBeDeleted = NULL;
	}

}

int main()
{
	ListNode *pHead =  NULL;
	int data[] = {23, 45, 36, 12, 89};
	int size = sizeof(data)/sizeof(int);
	for(int i = 0; i < size; i++)
		AddToTailListNode(&pHead, data[i]);

	RemoveListNode(&pHead, data[3]);

	PrintListReversingly(pHead);

	return 0;
}
