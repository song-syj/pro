#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef struct CARD{
	char type;
	unsigned char num;
}CARD;

CARD seq[4][3];
CARD pair[2];
int card_total[3][10]; // 麻将最多数目
int card_input[3][10]; // 手上的麻将牌
int card_add[3][10];


// 判断是否顺子或者是3个
bool group3card(int card[])
{
	int num = 0;
	for (int i = 1; i < 10; i++) {
		if (card[i] == 0) {
			num ++;
			continue;
		}

		switch(card[i]) {
		case 1:
		case 2:
			if (i > 7) return  false;
			if(card[i+2] == 0 || card[i+1] == 0)
				return false;
		case 4:
			if (i > 8) return  false;
			if(card[i+2] != 0 && card[i+1]!= 0) {
				card[i] --;
				card[i+1] --;
				card[i+2] --;
				if (group3card(card))
					return true;
				card[i]++;
				card[i+1] ++;
				card[i+2] ++;
			}
			break;
		case 3:
			if(card[i+2] != 0 && card[i+1]!= 0) {
				card[i+1] --;
				card[i+2] --;
				if (group3card(card))
					return true;
				card[i+1] ++;
				card[i+2] ++;
			}
			card[i] -=3;
			if (group3card(card))
					return true;
			card[i] +=3;
		}
	}

	if (num == 9)
		return true;
	else
		return false;
}

bool mahj_win(int n)
{
	if (n %3 != 2)
		return false;
	else {
		int pair_num = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 1; j < 10; j++) {
				if (card_input[i][j] == 4) {
					pair_num += 2;
				} else if (card_input[i][j] == 2) {
					pair_num++;
				}
			}
		}
		// 都是一对的情况
		if (pair_num == n) 
			return true;
		else {
			// 找到一对， 检查剩余是否为3个顺子或者连续
			for (int i = 0; i <3; i++) {
				for (int j = 1; j < 10; j++) {
					if (card_input[i][j] >= 2) {
						card_input[i][j] -= 2;
						if (group3card(card_input[0]) &&
							group3card(card_input[1]) &&
							group3card(card_input[2]) )
							return true;
						card_input[i][j] += 2;
					}
				}
			}
		}
	}
	return false;
}


bool find_maj(int n, int remain, int j)
{
	if (remain == 0)
		return mahj_win(n);
	if (j %10 == 0) 
		return find_maj( n, remain, j+1);
	if (j >= 30)
		return false;

	if (card_total[j/10][j%10]>=1) {
			card_total[j/10][j%10]--;
			card_input[j/10][j%10]++;
			card_add[j/10][j%10]++;

			if (find_maj(n+1, remain-1, j))
				return true;
				
			card_add[j/10][j%10]--;
			card_input[j/10][j%10]--;
			card_total[j/10][j%10]++;
	} 

	return find_maj( n, remain, j+1);
}

int main()
{
	char str[29];
	cin >> str;
	for(int i = 0; i < 3; i++){
		for(int j = 1; j < 10; j++) {
			card_total[i][j] = 4;
			card_input[i][j] = 0;
			card_add[i][j] = 0;
		}
	}
	
	if (strlen(str) != 26) {
		cout << 0 << endl;
		return 0;
	}
	// deal with input card
	for (int i = 0; i < 26; i++) {
		if(*(str + i) == 'T')
		{
			 card_input[0][*(str + i -1) - '0']++; 
			 card_total[0][*(str + i -1) - '0']--;
		}

		if(*(str + i) == 'D')
		{
			 card_input[1][*(str + i -1) - '0']++; 
			 card_total[1][*(str + i -1) - '0']--;
		}

		if(*(str + i) == 'W')
		{
			 card_input[2][*(str + i -1) - '0']++;
			 card_total[2][*(str + i -1) - '0']--;
		}
	}

	bool flag = false;
	for (int i = 1; i <= 95; i+=3) {
		if (find_maj(strlen(str)/2, i, 1)) {
			flag = true;
			break;
		}
	}
	
	if (flag == true) {
		cout << 1 << endl;
		for (int j = 0; j < 3; j++)  {
			for (int k = 1; k < 10; k++)  {
				while(card_add[j][k]--) {
					cout << k;
					switch(j) {
					case 0:
						cout << "T";
						break;
					case 1:
						cout << "D";
						break;
					case 2:
						cout << "W";
						break;
					}
				}
			}
		}
		cout << endl;
		
	} else {

		cout << 0 << endl;
	}

	return 0;
}

