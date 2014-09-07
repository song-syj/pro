struct ListNode {
	int m_nValue;
	ListNode* m_pNext;
};

ListNode* MergeList(ListNode* pHead1, ListNode* pHead2)
{
	if(pHead1 == NULL)
		return pHead2;
	if(pHead2 == NULL)
		return pHead1;

	ListNode *pNewHead = NULL;
	if(pHead1->m_nValue < pHead2->m_nValue) {
		pNewHead = pHead1;
		pNewHead->m_pNext = MergeList(pHead1->m_pNext, pHead2);
	} else {
		pNewHead = pHead2;
		pNewHead->m_pNext = MergeList(pHead1, pHead2->m_pNext);
	}

	return pNewHead;
}

ListNode* MergeList(ListNode* pHead1, ListNode* pHead2)
{
	if(pHead1 == NULL)
		return pHead2;
	if(pHead2 == NULL)
		return pHead1;

	ListNode *pNewHead = NULL;
	ListNode *pNewTail = NULL;
	if(pHead1->m_nValue < pHead2->m_nValue) {
		pNewHead = pNewTail = pHead1;
		pHead1 = pHead1->m_pNext;
	} else {
		pNewHead = pNewTail = pHead2;
		pHead2 = pHead2->m_pNext;
	}

	while(pHead1 && pHead2) {
		if(pHead1->m_nValue < pHead2->m_nValue) {
			pNewTail->m_pNext = pHead1;
			pNewTail = pNewTail->m_pNext;
			pHead1 = pHead1->m_pNext;
		} else {
			pNewTail->m_pNext = pHead2;
			pNewTail = pNewTail->m_pNext;
			pHead2 = pHead2->m_pNext;
		}
	}
	
	if(pHead1 == NULL) {
		pNewTail->m_pNext = pHead2;
	}
	
	if(pHead2 == NULL) {
		pNewTail->m_pNext = pHead1;
	}
		
	return pNewHead;
}
