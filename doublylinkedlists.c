#include<stdio.h>

typedef struct Node {
	struct Node* prev;
	int data;
	struct Node* next;
} node_t;

node_t* addAfter(node_t* l, int data) {
	node_t* new = malloc(sizeof(node_t));
	new->data = data;
	if(l == NULL) {
		new->next = NULL;
		new->prev = NULL;
		return new;
	}
	new->prev = i;
	new->next = i->next;
	if(i->next) i->next->prev = new;
	i->next = new;
	return new;
	//or
	//node_t *new
	//if(i == NULL) return addBefore(NULL);
	//new = addBefore(i->next);
	//new->prev = i;
	//i->next = new;
	//return new;
}

node_t* tail(node_t* head) {
	node_t* p;
	for (p = head; p->next; p = p->next);
	return p;

void printListReverse(node_t* head) {
	node_t* p = tail(head);
	for (; p; p->prev) {
		printf("%d <- ", p->data);
	}
	printf("NULL\n");
}
void swap(int *i1, int *i2) {
	int tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;
}

void listSwap(node_t* i1, node_t* i2) {
	swap(&i1->data, &i2>data);
}

int compare(node_t* i1, node_t* i2) {
	return i1->data - i2->data;
}


node_t* nth(node_t* head, int n) {
	for(; head && n; head = head->next, n--);
	return head;
}

void qSort(node_t* head) {
	//HW
}

node_t* listRemove(node_t* i) {
	node_t* p = i->prev;
	if(p == NULL) p = i->next;
	if (i->next) i->next->prev = i->prev;
	if (i->prev) i->prev->next = i->next;
	free(i);
	while(p->prev) p = p->prev;
	return p;
}

void bubbleSort(node_t* l) {
	int *i, *j;
	for(i = l; i; i = i->next) {
		for(j = l; j->next; j = j->next) {
			if(compare(j, j->next) > 0) listSwap(j, j->next);
		}
	}
}

int main() {
	node_t* l = NULL;
	for(int i = 0; i < 10; i++) {
		l = addAfter(l, rand() % 100);
	}
	printListReverse(l);
	bubbleSort(l);
	printListReverse(l);
	listRemove(tail(head));
}
