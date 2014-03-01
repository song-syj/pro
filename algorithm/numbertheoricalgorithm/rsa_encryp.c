#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct rsa_key {
	 unsigned e;
	 unsigned p;
	 unsigned q;
	 unsigned long d;
	 unsigned long n;
}rsa_key;

unsigned randfrom(unsigned begin, unsigned end)
{
	 srand(time(NULL));
	 return (begin + (unsigned)((double)rand() / (RAND_MAX) * (end - begin + 1)));
}


unsigned mod_pow(unsigned x, unsigned pow,
				 unsigned long long mod)
{
	 unsigned long long res, num;

	 num = x % mod;
	 for(res = 1; pow; pow >>= 1) {
		  if(pow & 1)
			   res = (res * num) % mod;
		  num = (num * num) % mod;
	 }

	 return res;

}

int witness(unsigned x, unsigned num) 
{ 
	 unsigned t, u; 
	 unsigned long long x0, x1; 
	 long long i; 


	 t = 0; 
	 u = num - 1; 
	 while(!(u & 1)) { 
		  u >>= 1; 
		  t++; 
	 } 
	 
	 x0 = mod_pow(x, u, num); 

	 for(i = 0; i < t; i++) { 
		  x1 = (x0 * x0) % num; 

		  if(x1 == 1 && 
			 x0 != 1 && 
			 x0 != num - 1) 
			   return 1; 
		  x0 = x1; 
	 } 

	 if(x1 != 1) 
		  return 1; 

	 return 0; 
} 

int miller_rabin(unsigned num, unsigned times)
{
	 unsigned x;
	 int i;

	 if(!(num & 1))
		  return 0;
	 
	 for(i = 0; i < times; i++) {
		  x = randfrom(0, num - 1); /* num must be odd */
		  if(witness(x, num))
			   return 0;
	 }

	 return 1;
}


typedef struct reminder {
	 long long div;
	 long long x;
	 long long y;
}reminder;

reminder euclid_gcd(unsigned long long a, unsigned long long b)
{
	 reminder rd, rdplus;
	 if (b == 0) {
		  rd.div = a;
		  rd.x = 1;
		  rd.y = 0;
		  return rd;
	 }

	 rdplus = euclid_gcd(b , a % b);

	 rd.div = rdplus.div;
	 rd.x = rdplus.y;
	 rd.y = rdplus.x - a / b * rdplus.y;

	 return rd;
}

rsa_key rsa_generator()
{
	 unsigned p ;
	 unsigned q, e;
	 unsigned long long phi, d, n;

	 rsa_key key;
	 reminder rd;

	 p = randfrom(0x80000000,0xffffffff);
	 while((q = randfrom(0x80000000,0xffffffff)) == p);

	 phi = (p - 1) * (q - 1);
	 n = p * q;
	 
	 e = 10001;
	 
	 while((rd = euclid_gcd(e , phi)).div != 1)  e += 2;

	 if(rd.x < 0)
		  d = rd.x + phi;
	 else
		  d = rd.x;
	 
	 key.p = p;
	 key.q = q;
	 key.e = e;
	 key.d = d;
	 key.n = n;

	 return key;
}

unsigned rsa_encryp(unsigned info, rsa_key key)
{
	 return mod_pow(info, key.e, key.n);
}

unsigned rsa_decryp(unsigned info, rsa_key key)
{
	 return mod_pow(info, key.d, key.n);
}


int main()
{
	 unsigned message;
	 unsigned ciphertext;
	 
	 rsa_key key;
	 while(scanf("%u", &message) != EOF) {

		  key = rsa_generator();
		  printf("message: %d\n", message);
		  printf("key { \n");
		  printf("\t e = %u\n", key.e);
		  printf("\t d = %lu\n", key.d);
		  printf("\t p = %u\n", key.p);
		  printf("\t q = %u\n", key.q);
		  printf("\t n = %lu\n", key.n);
		  printf("} \n");
			   
		  ciphertext = rsa_encryp(message, key);
		  message = rsa_decryp(ciphertext, key);

		  printf("ciphertext: %d\n", ciphertext);
		  printf("message: %d\n", message);
	 }
		  
	 return 0;
}
