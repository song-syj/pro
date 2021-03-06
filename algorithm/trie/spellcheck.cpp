#include <iostream>
#include <cstring>

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
trie_print(_trie_node *pnode, char *str, int index)
{
	if(pnode == NULL)
		return;
	*(str+index) = pnode->data;
	if( pnode->is_word) {
		*(str+index+1) = '\0';
		cout << str << endl;
	}
	for(int i=0; i < ALPHABET_NUM; i++) {
		trie_print(pnode->next[i], str, index+1);
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

bool
trie_search(_trie_node *root, char *str)
{
	char *pstr;
	_trie_node *pnode;
	int offset;
	if(root == NULL || *str == '\0')
		return false;
	
	pstr = str;
	pnode = root;
	
	while(*pstr) {
		offset = *pstr - ALP_BASE;
		pnode = pnode->next[offset];
		if(pnode == NULL) {
			return false;
		}
		pstr++;
	}
	
	if(pnode->is_word)
		return true;
	else
		return false;
	
}

int main()
{
	char str[16];
	char tmp[18];
	int len;
	_trie_node *root;
	
	root = trie_create();
	while(cin >> str) {
		if(!strcmp(str, "#"))
			break;
		trie_insert(root, str);
	}

	while(cin >> str) {
		if(!strcmp(str, "#"))
			break;
		
		if(trie_search(root, str)) {
			cout << str
				 << " is correct"
				 << endl;
		} else {
			cout << str << ": ";
			len = strlen(str);
			//delete an alphabet
			for(int i = 0; i < len; i++) {
				memcpy(tmp, str, sizeof(char)*i);
				strcpy(tmp+i, str+i+1);
				if(trie_search(root, tmp))
					cout << tmp << " ";
			}

			//replace an alphabet
			for(int i = 0; i < len; i++) {
				strcpy(tmp, str);
				int here = tmp[i];
				for(int j = 'a'; j <= 'z'; j++) {
					if (j == here)
						continue;
					tmp[i] = j;
					if(trie_search(root, tmp))
						cout << tmp << " ";
				}
			}

			//insert an alphabet
			strcpy(tmp+1, str);
			len++;
			for(int i = 0; i < len; i++) {
				for(int j = 'a'; j <= 'z'; j++) {
					tmp[i] = j;
					if(trie_search(root, tmp))
						cout << tmp << " ";
				}
				tmp[i] = tmp[i+1];
			}

			cout << endl;

		}
	} 
	
	
	return 0;
}


















