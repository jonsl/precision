
#include <stdio.h>
#include <math.h>
#include "fp128.h"
#include "vec2.h"

int main() {
	// fixed point test
	uint4 a = set128xyzw(2, 0x80000000, 0, 0);
	printf("a = {%x, %x, %x, %x}", a.x, a.y, a.z, a.w);
	uint4 b = inc128(a);
	printf("b = {%x, %x, %x, %x}", b.x, b.y, b.z, b.w);
	uint4 c = neg128(b);
	printf("c = {%x, %x, %x, %x}", c.x, c.y, c.z, c.w);

	// double float test
	unsigned int const sizeof_double = sizeof(double);
	unsigned int const sizeof_float = sizeof(float);

	double d_one = -0.3987959604845946;
	double d_two = 0.4956332876876876;
	double d_a = d_one + d_two;

	vec2 ds_one = set2d(d_one);
	double one = (double)ds_one.x + (double)ds_one.y;
	vec2 ds_two = set2d(d_two);
	double two = (double)ds_two.x + (double)ds_two.y;

	double r;
	double result;

	// add2 test
	vec2 ds_a = add2(ds_one, ds_two);
	r = (double)ds_one.x + (double)ds_one.y + (double)ds_two.x + (double)ds_two.y;
	result = (double)ds_a.x + (double)ds_a.y;

	// sub2 test
	vec2 ds_s = sub2(ds_one, ds_two);
	r = ((double)ds_one.x + (double)ds_one.y) - ((double)ds_two.x + (double)ds_two.y);
	result = (double)ds_s.x + (double)ds_s.y;

	// mul2 test
	vec2 ds_m = mul2(ds_one, ds_two);
	r = ((double)ds_one.x + (double)ds_one.y) * ((double)ds_two.x + (double)ds_two.y);
	result = (double)ds_m.x + (double)ds_m.y;

	return 0;
}
