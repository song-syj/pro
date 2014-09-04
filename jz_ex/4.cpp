#include<iostream>

using namespace std;

void ReplaceBlank(char* string, int length)
{
	if(string == NULL || length <= 0)
		return;

	int original_length = 0;
	int number_blank = 0;

	int i = 0;
	while(string[i] != '\0') {
		original_length++;
		if(string[i] == ' ')
			number_blank++;
		i++;
	}

	int new_length = original_length + 2 * number_blank;
	if(new_length >= length) return;

	int index_new = new_length;
	int index_original = original_length;

	while(index_original >=0 && index_new > index_original) {
		if(string[index_original] == ' ') {
			string[index_new--] = '0';
			string[index_new--] = '2';
			string[index_new--] = '%';
		} else {
			string[index_new--] = string[index_original];
		}
		index_original--;
	}
}

int main()
{
	char str[50] = " We are happy. ";
	cout << str << endl;
	ReplaceBlank(str, 50);
	cout << str << endl;

	return 0;
}
