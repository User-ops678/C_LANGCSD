#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define DEBUG

typedef struct Movie {
	int length;
	char name[100];
	int year;
	float income;
} movie_t;

typedef struct Node {
	movie_t data;
	struct Node* next;
} node_t;

#ifdef DEBUG
void printList(node_t* head) {
	node_t* current = head->next;
	while (current != NULL) {
		printf("[%d %s %d %f] -> ", current->data.length, current->data.name, current->data.year, current->data.income);
		current = current->next;
	}
	printf("[NULL]\n");
}
#endif
void fprintList(const char *, node_t *);
void reset(const char *);
//void list_after(const char *, int, node_t *);
//void delete(const char *, char *, node_t *);
void list_all(const char *);
void add(node_t *, const char *, float);
node_t* loadFromFile(FILE *);
void saveToFile(node_t *, FILE *f);
node_t* removeFront(node_t *);
node_t* removeElt(node_t *, node_t *);
node_t* find(node_t *, char *);
void addNode(node_t *, char *, int, float);
node_t* addFront(node_t *, movie_t);


int main(int argc, char *argv[]) {
	node_t* head = malloc(sizeof(node_t));
	head->next = NULL;
	FILE *f = fopen("movies.dat", "rb+");
	//if (head == NULL) {
	//	fprintf(stderr, "Could not allocate memory for head!\n");
	//	exit(EXIT_FAILURE);
	//}
	switch(argc) {
		case 2:
			//--reset or --list-all
			if (strcmp(argv[1], "--reset") == 0) {
				//--reset
				reset("movies.dat");
				printf("Successfully reset file!\n");
				break;
			} else if (strcmp(argv[1], "--list-all") == 0) {
				head = loadFromFile(f);
				printList(head);
				break;
			} else {
				fprintf(stderr, "Unknown option %s!\n", argv[1]);
				free(head);
				exit(EXIT_FAILURE);
			}
		case 3:
			//--delete or --list-after
			if (strcmp(argv[1], "--list-after") == 0) {
				//list_after("movies.dat", argv[2], head);
				break;
			} else if (strcmp(argv[1], "--delete") == 0) {
				head = loadFromFile(f);
				printf("loadFromFile successfully completed!\n");
				node_t* elt = find(head, argv[2]);
				printf("find successfully completed!\n");
				removeElt(head, elt);
				printf("removeElt successfully completed!\n");
				break;
			} else {
				fprintf(stderr, "Unknown option %s!\n", argv[1]);
				free(head);
				exit(EXIT_FAILURE);
			}
		case 4:
			//--add
			const char *movieName = argv[2];
			head = loadFromFile(f);
			//float amount = atof(argv[3]);
			//add(head, "movies.dat", amount);
			saveToFile(head, f);
			break;
		case 5:
			char *name = argv[2];
			int year = atoi(argv[3]);
			float income = atof(argv[4]);
			addNode(head, name, year, income);
			saveToFile(head, f);
			printf("Inserted: ");
			printList(head);
			break;
		default:
			//wrong use!
			fprintf(stderr, "Usage: %s <option> [arguments]\n", argv[0]);
			free(head);
			exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

node_t* createNode(char name[100], int year, float income) {
	node_t* newNode = (node_t*) malloc(sizeof(node_t));
	if(newNode == NULL) {
		fprintf(stderr, "Could not write new movie!\n");
		exit(EXIT_FAILURE);
	}
	newNode->data.length = strlen(name) + 1;
	strcpy(newNode->data.name, name);
	newNode->data.year = year;
	newNode->data.income = income;
	newNode->next = NULL;
	return newNode;
}
void addNode(node_t* head, char *name, int year, float income) {
	node_t* newNode = createNode(name, year, income);
	newNode->next = head->next;
	head->next = newNode;
	return;
}
void reset(const char *filename) {
	FILE *f = fopen(filename, "wb");
	if (f == NULL) {
		fprintf(stderr, "Could not reset file!\n");
		exit(EXIT_FAILURE);
	}
	fclose(f);
}
void list_all(const char *filename) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		fprintf(stderr, "Could not open file!\n");
		exit(EXIT_FAILURE);
	}
	node_t* head = loadFromFile(f);
	fclose(f);
	if(head) {
		printList(head);
	}else {
		printf("[NULL]\n");
	}
}
node_t* addFront(node_t* head, movie_t data) {
	node_t* new = malloc(sizeof(node_t));
	if(new == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	new->data = data;
	new->next = head;
	return new;
}
node_t* loadFromFile(FILE *f) {
	if (f == NULL) {
		fprintf(stderr, "Error: File pointer is NULL.\n");
		return NULL;
	}
	rewind(f);
	printf("File pointer reset. Attempting to read...\n");
	node_t* head = malloc(sizeof(node_t));
	movie_t data;
	while (fread(&data, sizeof(movie_t), 1, f) == 1) {
		head = addFront(head, data);
		printf("Reading: [%d %s %d %f]...\n", data.length, data.name, data.year, data.income);
	}
	if (head == NULL) {
		printf("No data read from file.\n");
	}
	return head;
}
node_t* removeFront(node_t* head) {
	if (head == NULL) {
		return NULL;
	}
	node_t* tail = head->next;
	free(head);
	return tail;
}
node_t* removeElt(node_t *head, node_t* elt) {
	if (head == elt) {
		return removeFront(head);
	}
	if (head == NULL) {
		fprintf(stderr, "Either there are no movies to remove or movie not found!\n");
		return NULL;
	}
	head->next = removeElt(head->next, elt);
	return head;
}
node_t* find(node_t* head, char *data) {
	if (head == NULL || data == NULL) {
		return NULL;
	}
	for(node_t* l = head->next; l != NULL; l = l->next) {
		if(l->data.name == NULL) {
			printf("Warning: Node with NULL name enountered.\n");
			continue;
		}
		if(l->data.name && strcmp(l->data.name, data) == 0) {
			return l;
		}
	}
	return NULL;
}
void saveToFile(node_t* head, FILE *f) {
	if (f == NULL) {
		fprintf(stderr, "File not open!\n");
		exit(EXIT_FAILURE);
	}
	rewind(f);
	node_t* current = head->next;
	while (current != NULL) {
		printf("Saving: [%d %s %d %f]\n", current->data.length, current->data.name, current->data.year, current->data.income);
		fwrite(&(current->data), sizeof(movie_t), 1, f);
		current = current->next;
	}
	fflush(f);
}
