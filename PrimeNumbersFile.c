#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define true 1
#define false 0
typedef int bool;

bool isPrime(int number) {
	if (number <= 1) {
		return false;
	}
	for (int i = 2; i <= sqrt(number); i++) {
		if (number % i == 0) {
			return false;
		}
	}
	return true;
}

void generateprimes() {
	int N;
	printf("Enter the upper limit: ");
	scanf("%d", &N);
	FILE *file;
	file = fopen("primes.txt", "w");
	for (int num = 2; num <= N; num++) {
		if (isPrime(num)) {
			fprintf(file, "%d\n", num);
		}
	}
	fclose(file);
	printf("Numbers up to %d have been saved in primes.txt\n", N);
}


int main() {
	generateprimes();
}
	
