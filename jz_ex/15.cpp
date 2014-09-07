struct ListNode
{
	int m_nValue;
	ListNode* m_pNext;
};

ListNode* FindKthToTail(ListNode* pListHead, usigned int k)
{
	if(pListHead == NULL || k == 0) return NULL;
	
	ListNode *pAhead = pListHead;
	ListNode *pBehind = NULL;
	
	for(int i = 0; i < k-1 && pAhead != NULL; i++) {
		pAhead = pAhead->m_pNext;
	}

	if(pAhead == NULL)
		return NULL;

	pBehind = pListHead;
	while(pAhead->m_pNext) {
		pAhead = pAhead->m_pNext;
		pBehind = pBehind->m_pNext;
	}

	return pBehind;
}
