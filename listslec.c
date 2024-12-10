#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>


typedef struct item {
	int data;
	struct item *next;
} list_t;

list_t* empty_list() {
	return NULL;
}
list_t* addFront(list_t* head, int data) {
	list_t* new = malloc(sizeof(list_t)); //struct item* new = malloc(sizeof(struct item));
	if (new == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	new->data = data;
	new->next = head;
	return new;
}


//Cannot be called on an empty list
void addAfter(list_t* elt, int data) {
	assert(elt != NULL);
	//list_t* new = malloc(sizeof(list_t));
	//new->data = data;
	//new->next = elt->next;
	//elt->next = new;
	elt->next = addFront(elt->next, data);
}


list_t* addLast(list_t* head, int data) {
	if(head == NULL) {
		return addFront(head, data);
	}	
	//1st way:
	//list_t* l;
	//for(l = list; l->next != NULL; l = l->next);
	//addAfter(l, data);
	//2nd way:
	head->next = addLast(head->next,data);
	return head;
}


list_t* find(list_t* head, int data) {
	for(list_t* l = head; l != NULL && l->data != data; l = l->next) {
	//return l;
		if(l->data == data) return l;
	}
	//return NULL;
}

list_t *removeFront(list_t* head) {
	list_t* tail = head->next;
	free(head);
	return tail;
}
//Cannot be called on an empty list
void removeAfter(list_t* head) {
	head->next = removeFront(head->next);
}

list_t* removeElt(list_t* head, list_t *elt) {
	if (head == elt) {
		return removeFront(head);
	}
	if (head == NULL) {
		return NULL;
	}
	//Tropos me epanalhpsi:
	//list_t* l = head;
	//for(l = head; l && l->next == elt; l = l->next);
	//list_t* d = l->next
	//l->next = l->next->next;
	//free(d);
	//return head;
	//Anadromikos tropos:
	head->next = removeElt(head->next, elt);
	return head;
}

void printList(list_t* head) {
	list_t* l;
	for(l = head; l; l = l->next) {
		printf("%d -> ", l->data);
	}
	printf("NULL\n");
}

void list_to_file(list_t* head, FILE *f) {
	rewind(f);
	list_t* l;
	for(l = head; l; l = l->next) {
		fwrite(&l->data, sizeof(int), 1, f);
	}
}

list_t* list_from_file(FILE *f) {
	list_t* head = empty_list();
	int data;
	for(;;) {
		fread(&data, sizeof(int), 1, f);
		if (!feof(f)) break;
		head = addFront(head, data);
	}
	return head;
}

int main(int argc, char *argv[]) {
	list_t* ptr;
	FILE *f;
	f = fopen("numbers.dat", "rb+");
	if (f == NULL) {
		return -2;
	}
	list_t* list;
	//list_t* list = empty_list();
	//list = addFront(list, 42);
	//list = addFront(list, 4);
	//list = addFront(list, 2);
	//list = addFront(list, 5);
	//list = addFront(list, 100);
	//list = add_front(list, 42);
	//list = add_front(list, 42);
	//list = add_front(list, 42);
	//list = add_front(list, 42);
	//ptr = find(list, 42);
	//printList(list);

	if(argc >= 2) {
		if(strcmp(argv[1], "--insert") == 0) {
			list = addLast(list, 22);
		}
		if(strcmp(argv[1], "--delete") == 0) {
			removeAfter(list);
		}
		list_to_file(list, f);
		printList(list);
		list = list_from_file(f);
	}
}
