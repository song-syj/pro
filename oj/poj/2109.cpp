#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

#define LEN 1802
#define LOP 12
#define END (LEN - 2)

char * integer_multiply(const char *a, const char *b, char *result)
{
	int la, lb, op, first, i, j, k;
	int tmp[LEN];

	la = strlen(a);
	lb = strlen(b);
	
	memset(tmp, 0, sizeof(int) * LEN);

	first = END;
	for(i = la - 1; i >= 0; i-- ) {
		k = first--;
		op = a[i] - '0';
		
		for(j = lb - 1; j >= 0; j--) {
			tmp[k--] += (b[j] - '0') * op;
		}
	}

	
	for(i = END; i >= k; i--) {
		tmp[i - 1] += tmp[i] / 10;
		result[i] = tmp[i] % 10 + '0';
	}

	while(k < END && result[k] == '0')
		k++;
	
	return result + k;
}

char *integer_pow(const char *x, int n, char *result)
{	

	char *str;
	int ver = 0;
	int bit = 0;
	
	result[END] = '1';
	
	while(n > 0) {
		ver <<= 1;
		ver += n & 1;
		n >>= 1;
		bit++;
	}
	
	str = result + END;
	while(bit-- > 0) {
		str = integer_multiply(str, str, result);
		if(ver & 1)
			str = integer_multiply(x, str, result);
		ver >>= 1;
	}
	
	return str;
}

int integer_compare(char *a, char *b)
{
	int la, lb;
	
	la = strlen(a);
	lb = strlen(b);
	
	if(la > lb)
		return 1;
	if(la < lb)
		return -1;

	for(int i = 0 ; i < la; i++) {
		if(a[i] > b[i])
			return 1;
		if(a[i] < b[i])
			return -1;
	}

	return 0;
			
}

int main()
{
	int pl, kl;
	char strp[LEN];
	char res[LEN];
	char strk[LOP];
	int n , cmp;
	int head, mid, tail;
	char *ps;

	while(std::cin >> n >> strp) {
		pl = strlen(strp);
		kl = pl / n;
		if (pl > n * kl)
			kl++;
		
		memset(res, 0, sizeof(char) * LEN);
		memset(strk, 0, sizeof(char) * LOP);
		
		head = (int)pow(10.0, kl - 1);
		tail = (int)pow(10.0, kl) - 1;
		
		while(head <= tail) {
			mid = (head + tail) >> 1;
			sprintf(strk, "%d", mid);
			ps = integer_pow(strk, n, res);
			
			cmp = integer_compare(ps, strp);
			if(cmp > 0)
				tail = mid - 1;
			else if(cmp < 0)
				head = mid + 1;
			else
				goto PUTOUT;
			}
		
		//std::cout << k << std::endl;
	PUTOUT:
		std::cout << strk
				  << std::endl;
	}
		
	
	return 0;
}
