#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Movie {
	int length;
	char *name;
	int year;
	float income;
} movie_t;
typedef Node {
	movie_t* data;
	struct Node *next;
} node_t;

node_t* createNode(char *name, int year, float income) {
	node_t* newNode = (node_t*) malloc(sizeof(node_t));
	newNode->data->name = name;
	newNode->data->year = year;
	newNode->data->income = income;
	newNode->next = NULL;
	return newNode;
}

void addMovie(node_t* head, char *name, int year, float income) {
	node_t* newNode = createNode(name, year, income);
	node_t *tmp = head->next;
	head->next = newNode;
	newNode->next = tmp;
	return;
}

int main() {
	
