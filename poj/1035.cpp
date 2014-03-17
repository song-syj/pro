#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;
#define ALPHABET_NUM 26
#define ALP_BASE 'a'
typedef struct node {
	void *data;
	struct node *next;
}list_node;

typedef int (*hash_code)(void *data);

typedef struct hashtaleb {
	list_node *ptr;
	int size;
	hash_code map;
}list_hash;

list_node *
node_create(void *data)
{
	list_node *pnew;
	pnew = (list_node *)malloc(sizeof(list_node));
	if(pnew == NULL) {
		cout << "create node error!" << endl;
		exit(0);
	}
	pnew->data = data;
	pnew->next = NULL;
	
	return pnew;
}

list_hash *
hash_create(int size, hash_code map)
{
	list_hash *plh;
	plh = (list_hash *)malloc(sizeof(list_hash));
	if(plh == NULL) {
		cout << "creat hash error" << endl;
		exit(0);
	}

	plh->ptr = (list_node *)malloc(sizeof(list_node)*size);
	if(plh->ptr == NULL) {
		cout << "creat list error" << endl;
		exit(0);
	}
	
	memset(plh->ptr, 0, sizeof(list_node)*size);
	plh->size = size;
	plh->map = map;

	return plh;
}

int str_hash(void *str)
{
	if(str == NULL)
		exit(0);
	return strlen((char *)str);
}

void
hash_insert(list_hash *plh, char *str)
{
	int hash_value, str_size;
	void *data;
	list_node *pnode;

	if(str == NULL || plh == NULL)
		return;

	hash_value = plh->map(str);
	pnode = &((plh->ptr)[hash_value]);

	while(pnode->next != NULL) {
		if(!strcmp((char *)(pnode->next->data), str))
			return;
		pnode = pnode->next;
	}

	str_size = strlen(str)+1;
	data = malloc(str_size * sizeof(char));
	if(data == NULL) {
		cout << "malloc data error!" << endl;
		exit(0);
	}
	memcpy(data, str, str_size * sizeof(char));
	
	pnode->next = node_create(data);
}


bool
hash_search(list_hash *plh, char *str)
{
	int hash_value;
	list_node *pnode;
	
	if(str == NULL || plh == NULL) {
		return false;
	}
	
	hash_value = plh->map(str);
	pnode = &((plh->ptr)[hash_value]);

	while(pnode->next) {
		if(!strcmp((char *)(pnode->next->data), str))
			return true;
	}
	
	return false;
}

void hash_print(list_hash *plh)
{
	for(int i = 0; i < plh->size; i++) {
		list_node *pnode = &(plh->ptr[i]);
		char c = i + 'a';
		cout << c << " : ";

		while(pnode->next) {
			char *str = (char *)(pnode->next->data);
			cout << str
				 << " ";
			pnode = pnode->next;
		}
		cout << endl;
	}
}

bool
replace_check(char *str, char *src)
{
	int i ,diff = 0;
	int len = strlen(src);
	for(i = 0; i< len; i++) {
		if (*str !=  *src) {
			diff++;
			if (diff > 1)
				return false;
		}
		
	}

	return true;
}

bool
delete_cheak(char *str, char *src)
{
	int len, diff = 0;
	len = strlen(src);
	for(int i = 0; i < len; ) {
		if(src[i] != str[i]) {
			diff++;
			if(diff > 1)
				return false;
			str++;
		} else {
			i++;
		}
	}
	return true;
}


bool
add_check(char *str, char *src)
{
	int len, diff = 0;
	len = strlen(str);
	for(int i = 0; i < len; ) {
		if(src[i] != str[i]) {
			diff++;
			if(diff > 1)
				return false;
			src++;
		} else {
			i++;
		}
	}
	return true;

}

void
spell_check(list_hash *plh, char *str)
{
	int hash_value;
	list_node *pnode;
	char* word;
	
	if(str == NULL || plh == NULL) {
		return;
	}
	
	hash_value = plh->map(str);
	pnode = &((plh->ptr)[hash_value]);
	
	while(pnode->next) {
		word = (char *)(pnode->next->data);
		if(!strcmp(word, str)) {
			cout << str << " is correct" << endl;
			return ;
		} 
		pnode = pnode->next; 
	}

	cout << str << ":";
		
	pnode = &((plh->ptr)[hash_value]);
	while(pnode->next) {
		word = (char *)(pnode->next->data);
		if(replace_check(str, word)) 
			cout << word << " ";
		pnode = pnode->next; 
	}
	
	pnode = &((plh->ptr)[hash_value + 1]);
	while(pnode->next) {
		word = (char *)(pnode->next->data);
		if(add_check(str, word)) 
			cout << word << " ";
		pnode = pnode->next; 
	}
	
	pnode = &((plh->ptr)[hash_value - 1]);
	while(pnode->next) {
		word = (char *)(pnode->next->data);
		if(delete_cheak(str, word)) 
			cout << word << " ";
		pnode = pnode->next; 
	}

	cout << endl;
	
}

int main()
{
	char str[16];
	char tmp[18];
	int len;
	list_hash *phash;
	
	phash = hash_create(26, str_hash);
	while(cin >> str) {
		if(!strcmp(str, "#"))
			break;
		hash_insert(phash, str);
	}

	while(cin >> str) {
		if(!strcmp(str, "#"))
			break;
		spell_check(phash, str);
	}	
	// hash_print(phash);
	// while(cin >> str) {
	// 	if(!strcmp(str, "#"))
	// 		break;
		
	// 	if(trie_search(root, str)) {
	// 		cout << str
	// 			 << " is correct"
	// 			 << endl;
	// 	} else {
	// 		cout << str << ": ";
	// 		len = strlen(str);
	// 		//delete an alphabet
	// 		for(int i = 0; i < len; i++) {
	// 			memcpy(tmp, str, sizeof(char)*i);
	// 			strcpy(tmp+i, str+i+1);
	// 			if(trie_search(root, tmp))
	// 				cout << tmp << " ";
	// 		}

	// 		//replace an alphabet
	// 		for(int i = 0; i < len; i++) {
	// 			strcpy(tmp, str);
	// 			int here = tmp[i];
	// 			for(int j = 'a'; j <= 'z'; j++) {
	// 				if (j == here)
	// 					continue;
	// 				tmp[i] = j;
	// 				if(trie_search(root, tmp))
	// 					cout << tmp << " ";
	// 			}
	// 		}

	// 		//insert an alphabet
	// 		strcpy(tmp+1, str);
	// 		len++;
	// 		for(int i = 0; i < len; i++) {
	// 			for(int j = 'a'; j <= 'z'; j++) {
	// 				tmp[i] = j;
	// 				if(trie_search(root, tmp))
	// 					cout << tmp << " ";
	// 			}
	// 			tmp[i] = tmp[i+1];
	// 		}

	// 		cout << endl;

	// 	}
	// } 
		
	// return 0;
}
