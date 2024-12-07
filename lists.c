#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int value;
	struct Node* next;
} Node_t;

Node_t* createNode(int val);
void addNode(Node_t *ptr, int val);
void printList(Node_t* head);

int main() {
	Node_t *head;
	head->next = NULL;
	addNode(head, 10);
	addNode(head, 20);
	addNode(head, 30);
	printList(head);
}
Node_t* createNode(int value) {
	Node_t* newNode = (Node_t*) malloc(sizeof(Node_t));
	newNode->value = value;
	newNode->next = NULL;
	return newNode;
}
void addNode(Node_t* head, int value) {
	Node_t* newNode = createNode(value);
	Node_t* tmp = head->next;
	head->next = newNode;
	newNode->next = tmp;
	return;
}
void printList(Node_t* head) {
	Node_t* current = head->next;
	while (current != NULL) {
		printf("%d -> ", current->value);
		current = current->next;
	}
	printf("NULL\n");
}
