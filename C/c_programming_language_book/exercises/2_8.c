/* made this by accident */
unsigned leftrot(unsigned x, int n) {
	while(n > 0) {
		x = (x << 1) | 0x1;
		n--;
	}
	return x;
}

unsigned rightrot(unsigned x, int n) {
	while(n > 0) {
		if(x & 0x1 == 0x1) {
			x = x >> 1 | ~(~0 >> 1);
		} else {
			x = x >> 1;
		}
		n--;
	}
	return x;
}
