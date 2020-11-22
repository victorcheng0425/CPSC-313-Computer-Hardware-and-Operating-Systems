#include <stdio.h>

int main(int argc, char *argv[]) {

	struct person {
		char name[20];
		int age;
		char address[20];
		char city[20];
		char postal_code[6];
		char province[2];
	};

	const int NUM_PEOPLE = 100;
	struct person people[NUM_PEOPLE];

	printf("Size of struct person: %ld\n", sizeof(struct person));

	/* Find the youngest person. */
	int youngest_ndx = -1;
	int youngest_age = 1000;
	for (int i = 0; i < NUM_PEOPLE; i++) {
		printf("Address of person %d: %p\n", i, (void *)(people + i));
		if (people[i].age < youngest_age) {
			youngest_ndx = i;
			youngest_age = people[i].age;
		}
	}
	printf("Youngest age = %d\n", people[youngest_ndx].age);
}
