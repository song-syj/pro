#include<iostream>
#include<stdlib.h>

using namespace std;

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode * m_pLeft;
	BinaryTreeNode * m_pRight;
};

BinaryTreeNode *ConstructBinaryTree(int *preorder, int *inorder, int length)
{
	if(length <=0 
			|| preorder == NULL 
			|| inorder == NULL)
		return NULL;
	int rootValue = *preorder;
	int rootIndex = 0;

	while(rootIndex < length && inorder[rootIndex] != rootValue){
		rootIndex++;
	}

	if(rootIndex == length) {
		cout << "Invalid input." << endl;
		exit(1);
	}

	BinaryTreeNode *pRoot = new BinaryTreeNode;
	pRoot->m_nValue = rootValue;
	pRoot->m_pLeft = ConstructBinaryTree(preorder+1, inorder, rootIndex);
	pRoot->m_pRight = ConstructBinaryTree(preorder+rootIndex+1, inorder+rootIndex+1, length-rootIndex-1);

	return pRoot;
}

void PostorderTraverse(BinaryTreeNode *pRoot)
{
	if(pRoot == NULL) return;

	PostorderTraverse(pRoot->m_pLeft);
	PostorderTraverse(pRoot->m_pRight);
	cout << pRoot->m_nValue << " ";
}

int main()
{
	int preorder[] = {1, 2, 4, 7, 3, 5, 6, 8};
	int inorder[] = {4, 7, 2, 1 ,5 ,3, 8, 6};
	BinaryTreeNode *pRoot = ConstructBinaryTree(preorder, inorder, 8);

	PostorderTraverse(pRoot);

	cout << endl;

	return 0;
}
