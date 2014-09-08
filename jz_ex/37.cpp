struct ListNode {
	int m_nKey;
	ListNode *m_pNext;
};

unsigned int GetListLength(ListNode *pHead)
{
	unsigned int nLength = 0;
	while(pHead != NULL) {
		nLength++;
		pHead = pHead->m_pNext;
	}

	return nLength;
}

ListNode * FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2)
{
	unsigned int nLength1=GetListLength(pHead1);
	unsigned int nLength2=GetListLength(pHead2);

	int nLengthDif = nLength1 - nLength2;

	ListNode* pListHeadLong = pHead1;
	ListNode* pListHeadShort = pHead2;

	if(nLength1 < nLength2) {
		ListNode* pListHeadLong = pHead2;
		ListNode* pListHeadShort = pHead1;
	}

	for(int i = 0; i < nLengthDif; i++) {
		pListHeadLong = pListHeadLong->m_pNext;
	}

	while(pListHeadLong != NULL &&
			pListHeadShort != NULL &&
			pListHeadLong != pListHeadShort) {
		pListHeadLong = pListHeadLong->m_pNext;
		pListHeadShort = pListHeadShort->m_pNext;
	}

	return pListHeadLong;
}
