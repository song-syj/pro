struct ListNode {
	int m_nValue;
	ListNode* m_pNext;
};

ListNode *ReverseList(ListNode* pHead)
{
	if(pHead == NULL)
		return NULL;
	ListNode *pNewHead = NULL;
	ListNode *pNode = pHead;

	while(pNode != NULL) {
		ListNode *pNext = pNode->m_pNext;
		pNode->m_pNext = pNewHead;
		pNewHead = pNode;
		pNode = pNext;
	}

	return pNewHead;
}
