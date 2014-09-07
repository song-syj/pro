struct BinaryTreeNode {
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

void FindPath(BinaryTreeNode* pRoot, 
		int expectedSum, 
		std::vector<int>path,
	   	int currentSum)
{
	if(pRoot == NULL)
		return;

	currentSum += pRoot->m_nValue;
	path.push_back(pRoot->m_nValue);

	bool isLeaf = pRoot->m_pLeft == NULL && pRoot->m_pRight;

	if(currentSum  == expectedSum && isLeaf) {
		printf("A path is found :");
		for(int i = 0; i < path.size(); i++)
			printf("%d ", path[i]);

		printf("\n");
	}

	if(pRoot->m_pLeft != NULL) {
		FindPath(pRoot->m_pLeft, expectedSum, path, currentSum);
	}
	if(pRoot->m_pRight != NULL) {
		FindPath(pRoot->m_pRight, expectedSum, path, currentSum);
	}

	path.pop_back();
}

void FindPath(BinaryTreeNode* pRoot, int expectedSum)
{
	if(pRoot == NULL)
		return;
	std::vector<int> path;
	int currentSum = 0;
	FindPath(pRoot, expectedSum, path, currentSum);
}
