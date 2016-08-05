
#include <stdio.h>
#include <math.h>
#include "fp128.h"
#include "vec2.h"

int main() {
	// fixed point test
	uint4 a = set128(2, 0x80000000, 0, 0);
	uint4 b = inc128(a);
	uint4 c = neg128(a);

	// double float test
	unsigned int const sizeof_double = sizeof(double);
	unsigned int const sizeof_float = sizeof(float);

	double d_one = 0.3987959604845946;
	double d_two = 0.4956332876876876;
	double d_a = d_one + d_two;

	vec2 ds_one = set2(d_one);
	double one = (double)ds_one.x + (double)ds_one.y;
	vec2 ds_two = set2(d_two);
	double two = (double)ds_two.x + (double)ds_two.y;

	vec2 ds_a = add2(ds_one, ds_two);

	double r = (double)ds_one.x + (double)ds_one.y + (double)ds_two.x + (double)ds_two.y;

	double result = (double)ds_a.x + (double)ds_a.y;

	return 0;
}
