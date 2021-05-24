#include <stdio.h>
#include <time.h>

#define MAX_ELEMENT 20000
#define MAX_LOOP 100000

int binsearchexample(int, int[], int);
int binsearch(int, int[], int);

int main(int argc, char **argv) {
	int data[MAX_ELEMENT];
	int index;
	int n = 1;
	int i;
	clock_t time_taken;

	/* Init data array */
	for(i = 0; i < MAX_ELEMENT; ++i)
		data[i] = i;

	for(i = 0, time_taken = clock(); i < MAX_LOOP; ++i)
		index = binsearchexample(n, data, MAX_ELEMENT);
	time_taken = clock() - time_taken;

	printf("Element at index %i\n", index);
	printf("Binsearch example took %lu\n", (unsigned long) time_taken);


	for(i = 0, time_taken = clock(); i < MAX_LOOP; ++i)
		index = binsearch(n, data, MAX_ELEMENT);
	time_taken = clock() - time_taken;

	printf("Element at index %i\n", index);
	printf("Binsearch took %lu\n", (unsigned long) time_taken);

	return 0;
}

int binsearchexample(int x, int v[], int n) {
	int low, mid, high;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high)/2;
		if (x < v[mid])
			high = mid + 1;
		else if (x > v[mid])
			low = mid + 1;
		else /* found match */
			return mid;
	}
	return -1; /* no match */
}

int binsearch(int x, int v[], int n) {
	int low, mid, high;
	low = 0;
	high = n - 1;
	mid = (low+high) / 2;
	while (low <= high && x != v[mid]) {
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
		mid = (low+high) / 2;
	}
	return x == v[mid] ? mid : -1;
}
