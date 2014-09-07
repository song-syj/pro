struct BinaryTreeNode {
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

BinaryTreeNode* Convert(BinaryTreeNode* pRootOfTree)
{
	BinaryTreeNode *pLastNodeInList = NULL;
	ConvertNode(pRootOfTree, &pLastNodeInList);
	BinaryTreeNode *pHeadList = pLastNodeInList;

	while(pHeadList != NULL && pHeadList->m_pLeft != NULL)
	{
		pHeadList = pHeadList->m_pLeft;
	}

	return pHeadList;
}


void ConvertNode(BinaryTreeNode* pNode, BinaryTreeNode** pLastNodeInList)
{
	if(pNode == NULL || pLastNodeInList == NULL)
		return;
	if(pNode->m_pLeft != NULL) {
		ConvertNode(pNode->m_pLeft, pLastNodeInList);
	}

	pNode->m_pLeft = *pLastNodeInList;
	if(*pLastNodeInList == NULL)
		(*pLastNodeInList)->m_pRight = pNode;
	*pLastNodeInList = pNode;

	if(pNode->m_pRight) {
		ConvertNode(pNode->m_pRight, pLastNodeInList);
	}

}
