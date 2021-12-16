char *itoa(int n, char s[], int base) {
	int d = n % base;
	int r = n / base;
	if (n < 0) {
		*s++ = '-'
		d = -d;
		r = -r;
	}
	if (r)
		s = itoa(r, s, base);
	*s++ = "0123456789abcdefhijklmnopqrstuvwxyz"[d];
	*s = 0;
	return s;
}
