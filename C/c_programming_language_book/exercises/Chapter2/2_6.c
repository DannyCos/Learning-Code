#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
	/* Steps:
		First, set n bits at position p in x to 0. ie. xx0000xxxxxxxxxx
			Do this by
			Anding x with the leftmost bits before position p set to 1, and all other bits set to 0
			Or that results with all bits after before p-n set to 0
		Extract n bits in y.
		Shift y left by p + 1 - n to put bits in position
		Or 2 results
		return. */
	return ((x & ((~0 << (p + 1)))) | (~(~0 << (p + 1 - n)))) | ((~(~0 << n) & y) << (p + 1 - n));
}
