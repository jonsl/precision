#pragma once

typedef struct _vec2 {
	float x;
	float y;
} vec2;

static inline vec2 set2(double a) {
	vec2 b;
	b.x = (float)a;
	b.y = (float)(a - b.x);
	return b;
}

static inline vec2 set2(float a) {
	vec2 b;
	b.x = a;
	b.y = 0.f;
	return b;
}

static inline vec2 set2(float a, float b) {
	vec2 c;
	c.x = a;
	c.y = b;
	return c;
}

// Based on dsadd from DSFUN90, analysis by Norbert Juffa from NVIDIA.
// For a and b of opposite sign whose magnitude is within a factor of two
// of each other either variant below loses accuracy. Otherwise the result
// is within 1.5 ulps of the correctly rounded result with 48-bit mantissa.
// This function computes c = a + b.
static inline vec2 add2(const vec2 a, const vec2 b) {
	vec2 c;
	float t1, e, t2;

	// Compute dsa + dsb using Knuth's trick.
	t1 = a.x + b.x;
	e = t1 - a.x;
	t2 = ((b.x - e) + (a.x - (t1 - e))) + a.y + b.y;

	// The result is t1 + t2, after normalization.
	c.x = e = t1 + t2;
	c.y = t2 - (e - t1);

	return c;
}

static inline vec2 neg2(vec2 a) {
	return set2(-a.x, -a.y);
}

// Based on dssub from DSFUN90
// This function computes c = a - b.
static inline vec2 sub2(const vec2 a, const vec2 b) {
	vec2 c;
	float t1, e, t2;

	// Compute dsa - dsb using Knuth's trick.
	t1 = a.x - b.x;
	e = t1 - a.x;
	t2 = ((-b.x - e) + (a.x - (t1 - e))) + a.y - b.y;

	// The result is t1 + t2, after normalization.
	c.x = e = t1 + t2;
	c.y = t2 - (e - t1);

	return c;
}

// This function multiplies DS numbers A and B to yield the DS product C.
static inline vec2 mul2(const vec2 a, const vec2 b) {
	vec2 c;

	// This splits dsa(1) and dsb(1) into high-order and low-order words.
	float cona = a.x * 8193.0f;
	float conb = b.x * 8193.0f;
	float sa1 = cona - (cona - a.x);
	float sb1 = conb - (conb - b.x);
	float sa2 = a.x - sa1;
	float sb2 = b.x - sb1;

	// Multilply a.x * b.x using Dekker's method.
	float c11 = a.x * b.x;
	float c21 = (((sa1 * sb1 - c11) + sa1 * sb2) + sa2 * sb1) + sa2 * sb2;

	// Compute a.x * b.y + a.y * b.x (only high-order word is needed).
	float c2 = a.x * b.y + a.y * b.x;

	// Compute (c11, c21) + c2 using Knuth's trick, also adding low-order product.
	float t1 = c11 + c2;
	float e = t1 - c11;
	float t2 = ((c2 - e) + (c11 - (t1 - e))) + c21 + a.y * b.y;

	// The result is t1 + t2, after normalization.
	c.x = e = t1 + t2;
	c.y = t2 - (e - t1);
	return c;
}
