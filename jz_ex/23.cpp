struct BinaryTreeNode {
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

void PrintFromTopToBottom(BinaryTreeNode* pTreeRoot)
{
	if(pTreeRoot) return;

	queue<BinaryTreeNode *> nodeQueue;
	nodeQueue.push(pTreeRoot);
	while(!nodeQueue.empty()) {
		BinaryTreeNode* pNode = queue.front();
		nodeQueue.pop();

		printf("%d ", pNode->m_nValue);

		if(pNode->m_pLeft) nodeQueue.push(pNode->m_pLeft);
		if(pNode->m_pRight) nodeQueue.push(pNode->m_pRight);
	}
}
