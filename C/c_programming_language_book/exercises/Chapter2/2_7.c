unsigned invert(unsigned x, int p, int n) {
	/*	Steps
		Create unsigned with 1's at position
			Shift 1's left by N
			Invert
			Shift left by P
		XOR x with above
		return
	*/

	return (~(~0 << n) << p) ^ x;
}
