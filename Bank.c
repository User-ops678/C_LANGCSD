#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct Account {
	int ID;
	char name[100];
	float balance;
	struct Account* next;
} Acc;

typedef struct Node {
	int data;
	struct Node* next;
} start;

struct Node* createNode(int value) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = value;
	newNode->next = NULL;
	return newNode;
}

void printList(struct Node* head) {
	struct Node* current = head;
	while (current != NULL) {
		printf("%d -> ", current->data);
		current = current->next;
	}
	printf("NULL\n");
}
void addNode(struct Node** head, int value) {
	struct Node* newNode = createNode(value);
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	struct Node* current = *head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = newNode;
}

struct Account* createAccount(const char* name, float firstDeposit) {
	struct Account* newAcc = (struct Account*)malloc(sizeof(struct Account));
	if (newAcc == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		return NULL;
	}
	srand(time(NULL));
	newAcc->ID = rand() % 1000000;
	strcpy(newAcc->name, name);
	newAcc->balance = firstDeposit;
	newAcc->next = NULL;
	printf("Account successfully created! Account ID: %d DO NOT SHARE THIS ID WITH ANYONE!\n", newAcc->ID);
	return newAcc;
}

void printAcc(struct Account* account) {
	if (account != NULL) {
		printf("Account ID: %d\n", account->ID);
		printf("Name: %s\n", account->name);
		printf("Balance $%.2f\n", account->balance);
	}
}

int main() {
	int sel;
	struct Node* head = NULL;
	while (1 == 1) {
		printf("1. Create account\n2. Login\n3. Deposit\n4. Withdraw\n5. Check Balance\n6. View Transaction History\n7. Exit\nChoice: ");
		scanf("%d", &sel);
		switch(sel) {
			case 1:
				struct Account* myAcc = createAccount("John Doe", 1000.0f);
				printAcc(myAcc);
				free(myAcc);
				exit(0);
			//case 2:
			//	Login();
			//case 3:
			//	Deposit();
			//case 4:
			//	Withdraw();
			//case 5:
			//	checkBalance();
			//case 6:
			//	viewTransactionHistory();
			case 7:
				exit(0);
			default:
				printf("Unknown option! Try again!\n");
				continue;
		}
	}
	addNode(&head, 10);
	//print
	printList(head);
}