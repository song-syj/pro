struct ListNode {
	int m_nValue;
	ListNode* m_pNext;
};

void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
{
	if(pListHead == NULL 
			|| *pListHead == NULL || 
			pToBeDeleted == NULL)
		return;

	if(pToBeDeleted->m_pNext !=NULL) {
		ListNode* pNext = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = pNext->m_nValue;
		pToBeDeleted->m_pNext = pNext->m_pNext;

		delete pNext;
		pNext = NULL;
	} else if(pToBeDeleted == *pListHead) {
		(*pListHead)->m_pNext = pToBeDeleted;

		delete pToBeDeleted;
		pToBeDeleted = NULL;
	} else {
		ListNode* pNode = *pListHead;
		while(pNode->m_pNext != pToBeDeleted)
			pNode = pNode->m_pNext;
		pNode->m_pNext = NULL;

		delete pToBeDeleted;
		pToBeDeleted = NULL;
	}
}
