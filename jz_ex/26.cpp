struct ComplexListNode {
	int m_nValue;
	ComplexListNode* m_pNext;
	ComplexListNode* m_pSibling;
};

void CloneNode(ComplexListNode *pHead)
{
	if(pHead == NULL)
		return;

	ComplexListNode* pNode = pHead;
	while(pNode != NULL) {
		ComplexListNode *pNew = new ComplexListNode;
		pNew->m_nValue = pNode->m_nValue;
		pNew->m_pNext = pHead->m_pNext;
		pHead->m_pNext = pNew;
		pNew->m_pSibling = NULL;

		pNode = pNew->m_pNext;
	}
}

void ConnectSiblingNodes(ComplexListNode* pHead)
{
	if(pHead == NULL)
		return;

	ComplexListNode* pNode = pHead;
	while(pNode != NULL) {
		if(pNode->m_pSibling != NULL) {
			pNode->m_pNext->m_pSibling = pNode->m_pSibling->m_pNext;
		}

		pNode = pNode->m_pNext->m_pNext;
	}
}

ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
	ComplexListNode* pCloneHead = NULL;
	ComplexListNode* pCloneNode = NULL;
	ComplexListNode* pNode = pHead;

	if(pNode != NULL) {
		pCloneNode = pCloneHead = pNode->m_pNext;
		pNode->m_pNext= pCloneNode->m_pNext;
		pNode = pNode->m_pNext;
	}

	while(pNode != NULL) {
		pCloneNode->m_pNext  = pNode->m_pNext;
		pCloneNode = pCloneNode->m_pNext;
		pNode->m_pNext= pCloneNode->m_pNext;
		pNode = pNode->m_pNext;
	}

	return pCloneHead;
}

ComplexListNode* Clone(ComplexListNode* pHead)
{
	CloneNode(pHead);
	ConnectSiblingNodes(pHead);
	return ReconnectNodes(pHead);
}
