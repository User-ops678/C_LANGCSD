#include<stdio.h>
struct employee {
	char *name;
	char title[20];
	char id[8];
	double salary;
	int years;
} e;

int main() {
	struct employee *e;
	e->years = 10;
	printf("%d\n", e->years);
}
