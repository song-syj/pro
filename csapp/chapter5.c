/* My solution to homework problems of chapter 5 in caspp
 * Date: 2014.03.06
 * Reference: Stackverflow website and others
 */

/* 5.15 */
/* A. There is a dependency between successive values of program value sum stored in register %xmm1. The loop computes a new value for sum by adding the old value with the product of udata[i] and vdata[i] stored in register %xmm0; Another dependency between succesive values of program vaule i. */

/* B. The latency of the floating-point adder limits the CPE to at best 3. */

/* C.The CPE is 1.00 for integer data. */

/* D. The multiplications performed by this routine are of the general form udata[i]*vdata[i]. 
   These are logically independent of each other. Hence the multiplier can execute them in a pipelined fashion. */

/* 5.16 */
void inner5(vec_ptr u, vec_ptr v, data_t *dest)
{
	 long int i;
	 int length = vec_length(u);
	 int limit = lenght - 3;
	 data_t *udata = get_vec_start(u);
	 data_t *vdata = get_vec_start(v);
	 data_t sum = (data_t) 0;

	 for (i = 0; i < limit; i += 4) {
		  sum  += udata[i] * vdata[i]
			   + udata[i+1] * vdata[i+1]
			   + udata[i+2] * vdata[i+2]
			   + udata[i+3] * vdata[i+3];
	 }

	 for(; i < length; i++)
		  sum += udata[i] * vdata[i];
	 
	 *dest = sum;
}

/* A. We must perform two loads per element to read values for udata and vdata. There is only one unit to perform these loads, and it requires one cycle. */
/* B. float computation can't associate.Therefore a latency of float addition is still CPE of 3.00 */

/* 5.17 */

void inner6(vec_ptr u, vec_ptr v, data_t *dest)
{
	 long int i;
	 int length = vec_length(u);
	 int limit = lenght - 2;
	 data_t *udata = get_vec_start(u);
	 data_t *vdata = get_vec_start(v);
	 data_t sum0 = sum1 = sum2 = (data_t)0;

	 for (i = 0; i < limit; i += 3) {
		  sum0 += udata[i] * vdata[i];
		  sum1 += udata[i+1] * vdata[i+1];
		  sum2 += udata[i+2] * vdata[i+2];
	 }

	 for(; i < length; i++)
		  sum0 += udata[i] * vdata[i];
	 
	 *dest = sum0 + sum1 + sum2;
}

/* A. For each element, we must perform two loads with a unit that can only load one value per clock cycle. We must also perform one ?oating-point multiplication with a unit that can only perform one multiplication every two clock cycles. Both of these factors limit the CPE to 2. */
/* B. There are not enough registers to hold intermediate variants IA32 when using three-way loop unrolling with three parallel. */

/* 5.18 */

void inner7(vec_ptr u, vec_ptr v, data_t *dest)
{
	 long int i;
	 int length = vec_length(u);
	 int limit = lenght - 2;
	 data_t *udata = get_vec_start(u);
	 data_t *vdata = get_vec_start(v);
	 data_t sum = (data_t) 0;

	 for (i = 0; i < limit; i += 3) {
		  sum  += (udata[i] * vdata[i]
				   + udata[i+1] * vdata[i+1]
				   + udata[i+2] * vdata[i+2]);

	 }

	 for(; i < length; i++)
		  sum += udata[i] * vdata[i];
	 
	 *dest = sum;
}

/* 5.19 */

void *optimized_memset(void *s, int c, size_t n)
{
	 size_t cnt ;
	 size_t remain;
	 unsigned long value ;
	 unsigned char *schar = (unsigned char *)s;
	 size_t k = sizeof(unsigned long);
	 unsigned long limit = n - k + 1;
	 unsigned long *sul;
	 
	 remain = k - (unsigned long)s % k;
	 c &= 0xff;
	 
	 for(cnt = 0, value = 0; cnt < k; cnt++) {
		  value <<= 8;
		  value |=  c;
	 }
	 
	 cnt = 0;
	 if (n >= k) {
		  while(cnt < remain) {
			   *schar++ = c;
			   cnt++;
		  }
		  
		  sul = (unsigned long *)schar;
		  for(; cnt < limit; cnt += k) {
			   *sul++ = value;
		  }
		  schar = (unsigned char *)sul;
	 }
	 
	 for(; cnt < n; cnt++) {
		  *schar++ = c ;
	 }
	 
	 return s;
}

/* 5.20 */
