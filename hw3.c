#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define DEBUG

typedef struct Movie {
	int length;
	char *name;
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
		printf("%d %s %d %f -> ", current->data.length, current->data.name, current->data.year, current->data.income);
		current = current->next;
	}
	printf("NULL\n");
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

int main(int argc, char *argv[]) {
	node_t* head = malloc(sizeof(node_t));
	head->next = NULL;
	FILE *f = fopen("movies.dat", "rb+");
	node_t* list;
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
				list_all("movies.dat");
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
				int i = 0;
				list = loadFromFile(f);
				node_t* elt = find(head, argv[2]);
				printf("Test %d\n", i);
				removeElt(head, elt);
				break;
			} else {
				fprintf(stderr, "Unknown option %s!\n", argv[1]);
				free(head);
				exit(EXIT_FAILURE);
			}
		case 4:
			//--add
			const char *movieName = argv[2];
			list = loadFromFile(f);
			//float amount = atof(argv[3]);
			//add(head, "movies.dat", amount);
			saveToFile(list, f);
			break;
		case 5:
			char *name = argv[2];
			int year = atoi(argv[3]);
			float income = atof(argv[4]);
			addNode(head, name, year, income);
			fprintList("movies.dat", head);
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

node_t* createNode(char *name, int year, float income) {
	node_t* newNode = (node_t*) malloc(sizeof(node_t));
	if(newNode == NULL) {
		fprintf(stderr, "Could not write new movie!\n");
		exit(EXIT_FAILURE);
	}
	newNode->data.length = strlen(name) + 1;
	newNode->data.name = name;
	newNode->data.year = year;
	newNode->data.income = income;
	newNode->next = NULL;
	return newNode;
}
void addNode(node_t* head, char *name, int year, float income) {
	node_t* newNode = createNode(name, year, income);
	node_t* tmp = head->next;
	head->next = newNode;
	newNode->next = tmp;
	return;
}
void fprintList(const char *filename, node_t* head) {
	FILE *f = fopen(filename, "ab");
	if(f == NULL) {
		fprintf(stderr, "Could not open file!\n");
		exit(EXIT_FAILURE);
	}
	node_t* current = head->next;
	while (current != NULL) {
		fwrite(current, sizeof(current), 4, f);
		current = current->next;
	}
}
void reset(const char *filename) {
	FILE *f = fopen(filename, "wb");
	if (f == NULL) {
		fprintf(stderr, "Could not reset file!\n");
		exit(EXIT_FAILURE);
	}
}
void list_all(const char *filename) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		fprintf(stderr, "Could not open file!\n");
		exit(EXIT_FAILURE);
	}
	node_t *ptr;
	fread(ptr, sizeof(node_t), 4, f);
	return;
}
node_t* loadFromFile(FILE *f) {
	node_t* head = NULL;
	movie_t data;
	for (;;) {
		fread(&data, sizeof(movie_t), 1, f);
		if (!feof(f)) break;
		addNode(head, data.name, data.year, data.income);
	}
	return head;
}
node_t* removeFront(node_t* head) {
	node_t* tail = head->next;
	free(head);
	return tail;
}
node_t* removeElt(node_t *head, node_t* elt) {
	int i = 0;
	if (head == elt) {
		return removeFront(head);
		printf("Test %d\n", i);
		i += 1;
	}
	if (head == NULL) {
		fprintf(stderr, "Either there are no movies to remove or movie not found!\n");
		return NULL;
	}
	head->next = removeElt(head->next, elt);
	printf("Test %d\n", i);
	i += 1;
	return head;
}
node_t* find(node_t* head, char *data) {
	int i = 0;
	for(node_t* l = head; l != NULL && strcmp(l->data.name, data) == 0; l = l->next) return l;
}
void saveToFile(node_t* head, FILE *f) {
	rewind(f);
	node_t* l;
	for(l = head; l; l->next) {
		fwrite(&l->data, sizeof(movie_t), 1, f);
	}
}
