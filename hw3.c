#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct movie {
	int length;
	char *name;
	int year;
	float income;
} movie_t;

void reset(FILE *f) {
	FILE *f = fopen("movies.dat", "w");
	fprintf(f, "");
	fclose(f);
}

movie_t insert(FILE *f, char *name, int year, int income) {
	movie_t *ptr = malloc(sizeof(movie_t));
	if (ptr == NULL) {
		fprintf(stderr, "Out of memory!");
		exit(EXIT_FAILURE);
	}
	strcpy(ptr->name, name);
	ptr->charlength = strlen(name) + 1;
	ptr->year = year;
	ptr->inclome = income;
	int charlength = strlen(name);
	FILE f = fopen("movies.dat", "a");
	fprintf("%d %s %d %f", charlength, name, year, income);
}

void delete(FILE *f, *arg) {
	FILE *f = fopen("movies.dat", "a");
	char* ch;
	FILE *f2 = fopen("temp.c", "w");
	int temp = 1;
	ch = getc(f);
	while(ch != EOF) {
		if (strcmp(ch, arg) == 0) {
			fprintf("");
		}
	}
}
int main(int argc, char *argv[]) {
	if (argc <
