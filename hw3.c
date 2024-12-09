#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DEBUG
#define SIZE 1000
typedef int bool;
#define true 1
#define false 0

typedef struct Movie {
	int length;
	char *name;
	char *year;
	char *income;
} movie_t;

typedef struct Node {
	movie_t data;
	struct Node* next;
} node_t;

node_t* createNode(char *, char *, char *);	
void addNode(node_t *, char *, char *, char *);
#ifdef DEBUG
void printList(node_t* head) {
	node_t* current = head->next;
	while (current != NULL) {
		printf("%d %s %s %s -> ", current->data.length, current->data.name, current->data.year, current->data.income);
		current = current->next;
	}
	printf("NULL\n");
}
#endif
void fprintList(const char *, node_t *);	
void reset(const char *);
//void list_after(const char *, char *);
void list_all(const char *);
void delete(const char *, char *);
void add(node_t *, const char *, double);
void loadFromFile(const char *, node_t *);
void saveToFile(const char *, node_t *);



int main(int argc, char *argv[]) {
	node_t* head = (node_t*) malloc(sizeof(node_t));
	if (head == NULL) {
		fprintf(stderr, "Could not allocate memory for head!\n");
		exit(EXIT_FAILURE);
	}
	head->next = NULL;
	switch(argc) {
		case 2:
			//--reset or --list-all
			if (strcmp(argv[1], "--reset") == 0) {
				//--reset
				reset("movies.dat");
				break;
			} else if (strcmp(argv[1], "--list-all") == 0) {
				//--list-all
				list_all("movies.dat");
				break;
			} else {
				fprintf(stderr, "Unknown option %s\n", argv[1]);
				exit(EXIT_FAILURE);
			}
		//case 3:
			//--delete or --list-after
			//if (argv[1] == "--list-after") {
			//	list_after("movies.dat", argv[2]);
			//	break;
			//}
		case 4:
			//--add
			const char *movieName = argv[2];
			loadFromFile("movies.dat", head);
			double amount = atof(argv[3]);
			add(head, movieName, amount);
			saveToFile("movies.dat", head);
			break;
		case 5:
			//--insert
			addNode(head, argv[2], argv[3], argv[4]);
			fprintList("movies.dat", head);
			printf("Insrted: ");
			printList(head);
			break;
		default:
			//wrong uasge
			fprintf(stderr, "Usage: %s <option> [arguments]\n", argv[0]);
			exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
node_t* createNode(char* name, char* year, char* income) {
	node_t* newNode = (node_t*) malloc(sizeof(node_t));
	if (newNode == NULL) {
		fprintf(stderr, "Could not write new movie!(OutOfMemoryException)\n");
		exit(EXIT_FAILURE);
	}
	newNode->data.length = strlen(name) + 1;
	newNode->data.name = strdup(name);
	newNode->data.year = strdup(year);
	newNode->data.income = strdup(income);
	if (!newNode->data.name || !newNode->data.year || !newNode->data.income) {
		fprintf(stderr, "Memory allocation for movie data failed!\n");
		free(newNode);
		exit(EXIT_FAILURE);
	}
	newNode->next = NULL;
	return newNode;
}
void addNode(node_t* head, char* name, char* year, char* income) {
	node_t* newNode = createNode(name, year, income);
	node_t* tmp = head->next;
	head->next = newNode;
	newNode->next = tmp;
	return;
}
void fprintList(const char *filename, node_t* head) {
	FILE *file = fopen(filename, "a");
	if (file == NULL) {
		fprintf(stderr, "Could not open to append file!\n");
		exit(EXIT_FAILURE);
	}
	node_t* current = head->next;
	while (current != NULL) {
		fprintf(file, "%d %s %s %s\n", current->data.length, current->data.name, current->data.year, current->data.income);
		current = current->next;
	}
}
void reset(const char *filename) {
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
		fprintf(stderr, "Could not reset file!\n");
		exit(EXIT_FAILURE);
	}
	printf("Successfully reset file!\n");
	fclose(f);
}
void list_all(const char *filename) {
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		fprintf(stderr, "Could not open file to read!\n");
		exit(EXIT_FAILURE);
	}
	char str[SIZE];
	while (fgets(str, SIZE, f) != NULL) {
		printf("%s", str);
	};
	fclose(f);
}

void add(node_t* head, const char *name, double amount) {
	node_t* current = head->next;
	while (current != NULL) {
		if (strcmp(current->data.name, name) == 0) {
			float currentIncome = atof(current->data.income);
			currentIncome += amount;
			char newIncome[50];
			snprintf(newIncome, sizeof(newIncome), "%.2f", currentIncome);
			free(current->data.income);
			current->data.income = strdup(newIncome);
			printf("Updated income for %s: %.2f\n", name, currentIncome);
			return;
		}
		current = current->next;
	}
	fprintf(stderr, "Movie %s not found in the list!\n", name);
}

void loadFromFile(const char *filename, node_t *head) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Could not open file to read!\n");
		return;
	}
	char line[SIZE];
	while(fgets(line, SIZE, file) != NULL) {
		int length;
		char name[SIZE], year[SIZE], income[SIZE];
		if (sscanf(line, "%d %s %s %s", &length, name, year, income) == 4) {
			addNode(head, name, year, income);
		} else {
			fprintf(stderr, "Skipping malformed line: %s", line);
		}
		fclose(file);
	}
}

void saveToFile(const char *filename, node_t *head) {
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "Could not open file to write!\n");
		exit(EXIT_FAILURE);
	}
	node_t* current = head->next;
	while (current != NULL) {
		fprintf(file, "%d %s %s %s\n", current->data.length, current->data.name, current->data.year, current->data.income);
		current = current->next;
	}
	fclose(file);
}
