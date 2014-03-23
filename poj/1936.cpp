#include<iostream>
#include<cstring>
using namespace std;

char seqt[100001];
char seqs[100001];

bool allinall(char *seqt, char *seqs);

int main()
{
	while(cin >> seqs >> seqt) {
		if(allinall(seqt, seqs)) 
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}


bool allinall(char *seqt, char *seqs)
{
	int lent, lens;
	int i, j;
	lent = strlen(seqt);
	lens = strlen(seqs);

	if(lens > lent)
		return false;
	if(lens == lent) {
		return !strcmp(seqt, seqs);
	}

	i = j = 0;
	while(i < lens &&
		  j < lent) {
		if(seqs[i] == seqt[j])
			i++;
		j++;
	}
	if(i == lens)
		return true;
	else
		return false;
}
