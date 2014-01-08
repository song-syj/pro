/* My solution to homework problems of chapter 2 in caspp
 * Date: 2012
 * Reference: Stackverflow website and others
 */
/* 2.58 */
char is_big_endian()
{
	short x = 1;

	return !*(char *)&x;
}

/* 2.59 */
(x | ~0xFF) | (y & 0xFF)

/* 2.60 */
unsigned put_byte(unsigned x, unsigned char b, int i)
{
	return (x & ~(0xFF << (i << 3))) | (b << (i << 3));
}

/* 2.61 */
A. !~x
B. !x
C. !(~x >> ((sizeof(int) - 1) << 3))
D. !(x & 0xFF)

/* 2.62 */
char int_shifts_are_logical()
{
	int x = ~0;
	
	return (x != (x >> 1))
}

/* 2.63 */
int sra(int x, int k)
{
	int xsrl = (unsigned) x >> k;
	int sign = 1 << (sizeof(int) << 3) - k -1;
	return ((sign << k) - (sign  & xsrl) << 1) + xsrl;
}


unsigned srl(unsigned x, int k)
{
	unsigned xsra = (int) x >> k;
	unsigned sign = 1 << (sizeof(int) << 3) - k - 1;
	return ~((sign << k) -sign << 1) & xsra;
}

/* 2.64 */
/*Return 1 when any even bit of x equals 1; 0 otherwise.
 *Assume w = 32
 */
int any_even_one(unsigned x)
{
	return (x& 0x55555555) == 0x55555555;
}

/* 2.65 */
/* Return 1 when x contains an even number of 1s; 0 otherwise;
 * Assume w = 32
 */
int even_ones(unsigned x)
{
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;

	return !(x & 1);
}

/* 2.66 */
/* Generate mask indicating leftmost 1 in x. Assume w = 32.
 * For example 0xFF00 -> 0x8000, and 0x6600 --> 0x4000
 * If x = 0, then return 0.
 */

int leftmost_one(unsigned x)
{
	/* use a technique called "bit smearing"
	 * to ensure that all the bits to
	 *the right of the first 1 are also 1 */
	x |= x >> 16;
	x |= x >> 8;
	x |= x >> 4;
	x |= x >> 2;
	x |= x >> 1;

	/* leave the highest bits */
	x ^= x >> 1;
}

/* 2.67 */

/* a function return 1 when run on a machine for which an int is 32bits
 * and return  0 otherwise.
 */
#include <limits.h>

int int_size_is_32()
{
	int set_msb = 0x80000000;
	
	return (set_msb == INT_MIN);
}

int int_size_is_at_least_32()
{
	int set_msb = 0x80000000;
	return !!set_msb;
}

int int_size_is_at_least_16()
{
	int set_msg = 0x8000;

	return !!set_msg;
}

/* 2.68 */

int lower_bits(int x, int n) {
	int mask = 1 << (n - 1)
		mask |= ~(~0 << (n - 1));

	return x & mask;
}

int lower_bits(int x, int n)
{
	int mask = ~(~0 << 1 << (n - 1));

	return x & mask;
}
