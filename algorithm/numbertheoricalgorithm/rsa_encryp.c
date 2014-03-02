#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>



typedef struct rsa_key {
	 uint64_t e;
	 uint64_t p;
	 uint64_t q;
	 uint64_t d;
	 uint64_t n;
}rsa_key;

uint64_t randfrom(uint64_t begin, uint64_t end)
{
	 srand(time(NULL));
	 return (begin + (uint64_t)((double)rand() / (RAND_MAX) * (end - begin + 1)));
}


uint64_t mod_pow(uint64_t x, uint64_t pow,
				 uint64_t mod)
{
	 uint64_t res, num;

	 num = x % mod;
	 for(res = 1; pow; pow >>= 1) {
		  if(pow & 1)
			   res = (res * num) % mod;
		  num = (num * num) % mod;
	 }

	 return res;

}

int witness(uint64_t x, uint64_t num) 
{ 
	 uint64_t t, u; 
	 uint64_t x0, x1; 
	 int64_t i; 


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

int32_t miller_rabin(uint64_t num, uint64_t times)
{
	 uint64_t x;
	 int32_t i;

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

reminder euclid_gcd(uint64_t a, uint64_t b)
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
	 uint64_t p ;
	 uint64_t q, e;
	 uint64_t phi, d, n;

	 rsa_key key;
	 reminder rd;

	 do {
		  p = randfrom(0x00008000,0x0000ffff);
	 }while(!miller_rabin(p, 10));
	 
	 do {
		  q = randfrom(0x00008000,0x0000ffff);
	 }while(!miller_rabin(q, 10) || p == q);
	 
	 phi = ((uint64_t)p - 1) * (q - 1);
	 n = p * q;
	 
	 e = 1000001;
	 
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

uint64_t rsa_encryp(uint64_t info, rsa_key key)
{
	 return mod_pow(info, key.e, key.n);
}

uint64_t rsa_decryp(uint64_t info, rsa_key key)
{
	 return mod_pow(info, key.d, key.n);
}


int32_t main()
{
	 uint64_t message;
	 uint64_t ciphertext;
	 
	 rsa_key key;
	 while(scanf("%llu", &message) != EOF) {

		  key = rsa_generator();
		  printf("message: %llu\n", message);
		  printf("key { \n");
		  printf("\t e = %llu\n", key.e);
		  printf("\t d = %llu\n", key.d);
		  printf("\t p = %llu\n", key.p);
		  printf("\t q = %llu\n", key.q);
		  printf("\t n = %llu\n", key.n);
		  printf("} \n");
			   
		  ciphertext = rsa_encryp(message, key);
		  message = rsa_decryp(ciphertext, key);

		  printf("ciphertext: %llu\n", ciphertext);
		  printf("message: %llu\n", message);
	 }
		  
	 return 0;
}
