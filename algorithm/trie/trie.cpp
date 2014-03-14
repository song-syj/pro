#include<iostream>
using namespace std;

#define ALPHABET_NUM 26
#define ALP_BASE 'a'

typedef struct trie_node {
	struct trie_node *next[ALPHABET_NUM];
	char data;
	bool is_word;
}_trie_node;

_trie_node * trie_create()
{
	_trie_node *root;
	
	root = new _trie_node;
	root->is_word = false;
	for(int i = 0; i < ALPHABET_NUM; i++)
		root->next[i] = NULL;
	
	return root;
}

void
trie_insert(_trie_node *root, char *str)
{
	char *pstr;
	int offset;
	_trie_node *pnode;
	if(root == NULL) {
		return;
	}
	
	pstr = str;
	pnode = root;

	while(*pstr) {
		offset = *pstr - ALP_BASE;
		if((pnode->next)[offset] == NULL) {
			pnode->next[offset] = trie_create();
		}
		pnode = pnode->next[offset];
		pnode->data = offset + ALP_BASE;
		
		pstr++;
	}
	pnode->is_word = true;
}

void
trie_print(_trie_node *pnode, char *str, int i)
{
	if(pnode == NULL)
		return;
	*(str+i) = pnode->data;
	if( pnode->is_word) {
		*(str+i+1) = '\0';
		cout << str << endl;
	}
	for(int i=0; i < ALPHABET_NUM; i++) {
		trie_print(pnode->next[i], str, i+1);
	}
	
}

void
trie_print_all(_trie_node *root, char *str)
{
	for(int i=0; i < ALPHABET_NUM; i++) {
		trie_print(root->next[i], str, 0);
	}
}

void
trie_delete(_trie_node *root)
{
	if (root == NULL)
		return;

	for(int i = 0; i < ALPHABET_NUM; i++) {
		if(root->next[i] != NULL) {
			trie_delete(root->next[i]);
		}
	}

	delete root;
}

int
main()
{
	int size;
	char str[101];
	_trie_node *root;
	
	root = trie_create();
	cin >> size;
	
	for(int i = 0; i < size; i++){
		cin >> str;
		trie_insert(root, str);
	}
	
	trie_print_all(root, str);

	trie_delete(root);
	return 0;
}


















