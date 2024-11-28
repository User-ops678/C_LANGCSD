#include<stdio.h>
#include<stdlib.h>

int addition(int a, int b) {
	int sum = a + b;
	return sum;
}

int subtraction(int a, int b) {
	int sub = a - b;
	return sub;
}

int multiplication(int a, int b) {
	int mult = a * b;
	return mult;
}

int division(int a, int b) {
	float result = 0;
	if (b != 0) {
		result = a / b;
	}
	else {
		fprintf(stderr, "Cannot divide by zero!\n");
		exit(1);
	}
	return result;
}

int main() {
	int x, y;
	int res;
	char symbol;
	printf("Enter 1st number: ");
	scanf("%d", &x);
	printf("Enter 2nd number: ");
	scanf("%d", &y);
	while (1 == 1) {
		printf("Enter symbol: ");
		scanf(" %c", &symbol);
		if (symbol == '+') {
			res = addition(x, y);
			break;
		} else if (symbol == '-') {
			res = subtraction(x, y);
			break;
		} else if (symbol == '*') {
			res = multiplication(x, y);
			break;
		} else if (symbol == '/') {
			res = division(x, y);
			break;
		} else {
			printf("Unknown symbol! try again!\n");
			continue;
		}
	}
	printf("%d %c %d = %d\n", x, symbol, y, res);
	return 0;
}
