#pragma once

//CPP

typedef unsigned int uint;

typedef struct _uint4 {
	uint x, y, z, w;
} uint4;

inline static uint4 set128(uint v) {
	uint4 a = { v, v, v, v };
	return a;
}

inline static uint4 set128xyzw(uint x, uint y, uint z, uint w) {
	uint4 a = { x, y, z, w };
	return a;
}

static inline uint4 eq128(uint4 a, uint4 b) {
	uint4 c = { a.x == b.x ? (uint)-1 : 0, a.y == b.y ? (uint)-1 : 0, a.z == b.z ? (uint)-1 : 0, a.w == b.w ? (uint)-1 : 0 };
	return c;
}

static inline uint4 lt128(uint4 a, uint4 b) {
	uint4 c = { a.x < b.x ? (uint)-1 : 0, a.y < b.y ? (uint)-1 : 0, a.z < b.z ? (uint)-1 : 0, a.w < b.w ? (uint)-1 : 0 };
	return c;
}

static inline uint4 add4(uint4 a, uint4 b) {
	return set128xyzw(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

// Return U+V
static inline uint4 add128(uint4 u, uint4 v) {
	uint4 s = add4(u, v);
	uint4 h = lt128(s, u);
	uint4 c1 = { h.y & 1, h.z & 1, h.w & 1, 0 }; // Carry from U+V
	h = eq128(s, set128(0xFFFFFFFF));
	uint4 c2 = set128xyzw((c1.y | (c1.z&h.z))&h.y, c1.z&h.z, 0, 0); // Propagated carry
	return add4(add4(s, c1), c2);
}

// Increment U
static inline uint4 inc128(uint4 u) {
	// Compute all carries to add
	uint4 h = eq128(u, set128(0xFFFFFFFF));	// Note that == sets ALL bits if true [6.3.d]
	uint4 c = set128xyzw(h.y&h.z&h.w & 1, h.z&h.w & 1, h.w & 1, 1);
	return add4(u, c);
}

// Return -U
static inline uint4 neg128(uint4 u) {
	return inc128(set128xyzw(u.x ^ (uint)-1, u.y ^ (uint)-1, u.z ^ (uint)-1, u.w ^ (uint)-1)); // (1 + ~U) is two's complement
}
