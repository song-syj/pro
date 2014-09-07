struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

void MirrorRecursively(BinaryTreeNode *pNode)
{
	if(pNode == NULL) return;
	if(pNode->m_pLeft == NULL
	   && pNode->m_pRight == NULL)
		return;

	BinaryTreeNode *tmp;
	tmp = pNode->m_pRight;
	pNode->m_pRight = pNode->m_pLeft;
	pNode->m_pLeft = tmp;

	if(pNode->m_pRight)
		MirrorRecursively(pNode->m_pRight);

	if(pNode->m_pLeft)
		MirrorRecursively(pNode->m_pLeft);
}
