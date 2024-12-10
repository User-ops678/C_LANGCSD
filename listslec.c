#include<stdio.h>
#include<assert.h>

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
		fpritnf(stderr, "Memory allocation failed!\n");
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
int main() {
	list_t* list = empty_list();
	list = add_front(list, 42);
	list = add_front(list, 4);
	list = add_front(list, 2);
	list = add_front(list, 5);
	list = add_front(list, 100);
	//list = add_front(list, 42);
	//list = add_front(list, 42);
	//list = add_front(list, 42);
	//list = add_front(list, 42);
}
