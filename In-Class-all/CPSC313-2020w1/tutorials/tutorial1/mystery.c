#include <stdio.h>

long array[] = {10, 1,  3,  5,  7, 9};

int main(int argc, char *argv[]) {

	long sum = 0;
	long *lp = array;
	long max = *lp++;

	while (sum < max) {
		sum += *lp++;
	}

	printf("%ld\n", sum);
}
