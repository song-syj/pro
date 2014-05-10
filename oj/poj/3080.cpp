#include<iostream>
#include<cstring>
using namespace std;
char prefix[60];
char dna_seq[10][61];
char dna_suffix[61];
void
compute_prefix(char *pattern, int m)
{
	int i , j = 0;
	
	prefix[0] = 0;
	for(i = 1; i < m; i++) {
		while(j > 0 && pattern[i] != pattern[j])
			j = prefix[j-1];
		if(pattern[i] == pattern[j]) j++;
		prefix[i] = j;
	}
}

bool
kmp_match(char *text, int n, char *pattern, int m)
{
	int i, j = 0;

	for(i = 0; i < n; i++) {
		while( j > 0 && text[i] != pattern[j]) j = prefix[j - 1];
		if(text[i] == pattern[j]) j++;
		if(j == m) return true;
	}

	return false;
}

int main()
{
	int group, number;
	int len_match = 0;
	int match_start;
	bool is_match;
	
	cin >> group;

	for(int i = 0; i < group; i++) {
		cin >> number;
		if(number < 2) {
			cout << "input number > 1" << endl;
			return -1;
		}

		len_match = 0;
		for(int j = 0; j < number; j++)
			cin >> dna_seq[j];
		for(int j = 0; j < 58; j++) {
			strcpy(dna_suffix, dna_seq[0]+j);
			compute_prefix(dna_suffix, 60 - j);
			for(int p = 3; p <= 60 - j; p++) {
				for(int q = 1; q < number; q++) {
					is_match = kmp_match(dna_seq[q], 60, dna_suffix, p);
					if(is_match == false)
						break;
				}
				
				if(is_match == false)
					break;
				else {
					if(len_match < p) {
							len_match = p;
							match_start = j;
					}
					if(len_match == p) {
						char *former , *later;
						former = dna_seq[0] + match_start;
						later = dna_seq[0] + j;
						if(strcmp(former, later) > 0) {
							len_match = p;
							match_start = j;
						}
					}
				}
			}
			
		}
		
		if(len_match > 0)  {
			char *pstr;
			pstr = dna_seq[0] + match_start;
			pstr[len_match] = '\0'; 
			cout << pstr << endl;
		} else {
			cout << "no significant commonalities" << endl;
		}
	}
			
	return 0;
}
