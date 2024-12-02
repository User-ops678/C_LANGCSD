#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
typedef int bool;


#define true 1
#define false 0


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


bool confirmExit() {
	char ans[3];
	printf("Are you sure you want to exit? (Y/N) ");
	scanf("%s", ans);
	if (ans[0] == 'y' || ans[0] == 'Y') {
		return true;
	}
	return false;
}

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

struct Account* Login(const int id) {
	struct Account* ID = (struct Account*)malloc(sizeof(struct Account));
	struct Account* Account;
	if (id == Account->ID) {
		printf("Login Successfull!\n");
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
				char accName[100];
				int Deposit;
				printf("Enter Account Name: ");
				scanf("%s", accName);
				printf("Enter First Deposit: ");
				scanf("%d", &Deposit);
				struct Account* myAcc = createAccount(accName, Deposit);
				printAcc(myAcc);
				free(myAcc);
				continue;
			case 2:
				int ID;
				printf("Enter Account ID: ");
				scanf("%d", &ID);
				Login(ID);
			//case 3:
			//	Deposit();
			//case 4:
			//	Withdraw();
			//case 5:
			//	checkBalance();
			//case 6:
			//	viewTransactionHistory();
			case 7:
				bool e = confirmExit();
				if (e == true) {
					exit(0);
				}
				continue;
			default:
				printf("Unknown option! Try again!\n");
				continue;
		}
	}
	addNode(&head, 10);
	//print
	printList(head);
}
