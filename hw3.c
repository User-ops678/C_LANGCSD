#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct movie {
	int length;
	char *name;
	int year;
	float income;
} movie_t;

typedef struct {
	movie_t *data;
	size_t n;
} file_data_t;

void reset(FILE *f) {
	FILE *f = fopen("movies.dat", "w");
	fprintf(f, "");
	fclose(f);
}

movie_t insert_movie(char *name, int year, int income) {
	movie_t *ptr = malloc(sizeof(movie_t));
	if (ptr == NULL) {
		fprintf(stderr, "Out of memory!");
		exit(EXIT_FAILURE);
	}
	strcpy(ptr->name, name);
	ptr->charlength = strlen(name) + 1;
	ptr->year = year;
	ptr->inclome = income;
	FILE f = fopen("movies.dat", "a");
	fprintf(f, "%d %s %d %f", ptr->charlength, ptr->name, ptr->year, ptr->income);
}

char *getFileContents(const char *);
file_data_t *insert_data(char *, const char *);

void delete(*arg) {
	char *buffer = getFileContents("movies.dat");
	file_data_t *file_data = insert_data(buffer, arg);
	free(buffer);
	FILE *fp = fopen("movies.dat", "w");
	if (fp == NULL) {
		fprintf(stderr, "Could not  open file: movies.dat");
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < file_data->n; i++) {
		fprintf(fp, "%ld %s %d %f", file_data->data[i].length, file_data->data[i].name, file_data->data[i].year, file_data->data[i].income);
		free(file_data->data[i].name);
		free(file_data->data[i].year);
		free(file_data->data[i].income);
		free(file_data->data[i].length);
	}
	free(file_data->data);
	free(file_data);
	fclose(fp);
	return EXIT_SUCCESS;
}


int main(int argc, char *argv[]) {
	switch(argc) {
		case 2:
			//then --reset or --sort is provided
			if(argv[1] == --reset) {
				reset_movies();
			} else if (argv[1] == --sort) {
				sort_movies();
			}
		case 3:
			//then --delete or --list-after is provided
			char arg = argv[1];
			if (arg == --delete) {
				char movie_to_delete = argv[2];
				delete(movie_to_delete);
			} else if (arg == --list-after) {
				int year = argv[2];
				list_after(year);
			}
		case 4:
			//then --add is provided
			char name = argv[3];
			int increase_income = argv[4];
			inc_income(name, increase_income);
		case 5:
			//then --insert is provided
			char name = argv[3];
			int year = argv[4];
			int income = argv[5];
			insert_movie(name, year, income);
		default:
			printf("Usage: %s --<option>", argv[0]);
			fprintf(stderr, "Available options: \nreset\nsort\ninsert <movie> <year> <income>\ndelete <movie>\nlist-all\nlist-after <year>\nadd <movie> <income>\n");
	}
}

file_data_t *insert_data(char *buffer, const char *dont_keep) {
	size_t buffersize = START_SIZE;
	char *token = NULL;
	char *rest = buffer;
	size_t count = 0;

	file_data_t *file_data = malloc(sizeof *file_data);
	if (file_data == NULL) {
		fprintf(stderr, "Could not allocate enough memory!\n");
		exit(EXIT_FAILURE);
	}
	file_data->data = malloc(buffsize * sizeof *file_data->data);
	if (file_data->data == NULL) {
		fprintf(stderr, "COuld not allocate enoght memory!\n");
		exit(EXIT_FAILURE);
	}
	while ((token = strtok_r(rest, &rest)) != NULL) {
		if (count == buffsize) {
			buffsize *= 2;
			void *ptr = realloc(file_data->data, buffsize * sizeof *file_data->data);
			if (ptr == NULL) {
				fprintf(stderr, "Could not allocate enough memory!");
