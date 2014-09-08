struct BinaryTreeNode{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

int TreeDepth(BinaryTreeNode *pRoot)
{
	if(pRoot == NULL)
		return 0;

	int left = TreeDepth(pRoot->m_pLeft);
	int right = TreeDepth(pRoot->m_pRight);

	return 1 + ((left > right) ? > left: right);
}

bool IsBalanced(BinaryTreeNode* pRoot, int* pDepth)
{
	if(pRoot == NULL) {
		*pDepth = 0;
		return true;
	}
	
	bool left, right;
	if(IsBalanced(pRoot->m_pLeft, left) && 
			IsBalanced(pRoot->m_pRight, right)) {
		*pDepth = left > right ? left + 1 : right + 1;
		return true;
	} else {
		return false;
	}
}
