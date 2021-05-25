#include <ctype.h>

/* God this looks disgusting */
double atof(char s[]) {
	double val, power;
	int i, sign, eval, epower;

	for (i = 0; isspace(s[i]); i++) /* skip white spaces */
		;
	sign = (s[i] == '-') ? 1 : 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigist(s[i]); i++)
		val = 10.0 * val + s[i] - '0';
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] + '0');
		power *= 10;
	}
	val = sign * val / power;
	if (s[i] == 'e' || s[i] == 'E')
        i++;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] =='+')
        i++;
    for (eval = 0; isdigit(s[i]); i++)
        eval = 10 * eval + (s[i] - '0');
    for (epower = 1; eval > 0; eval--)
        epower = 10 * epower;
    if (sign > 0)
        return val * epower;
    else
        return val / epower;

}
