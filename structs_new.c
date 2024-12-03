#include<stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct dob {
	int day;
	int month;
	int year;
} date_t;
struct person {
	char name[20];
	char surname[40];
	date_t dob;
};
typedef struct person person_t;
person_t *new_person(char *name, char *surname, int day, int month, int year) {
	person_t *ptr = malloc(sizeof(person_t));
	if(ptr == NULL) {
		fprintf(stderr, "Out of memory!");
		exit(-1)
	}
	strcpy(ptr->name, name);
	strcpy(ptr->surname, surname);
	ptr->dob.date = day;
	ptr->dob.month = month;
	ptr->dob.year = year;
}
void print_person(person_t *p) {
	printf("%s %s %d/%d/%d", p->name,p->surname,p->dob.day,p->dob.month,p->dob.year);
}
int compare1(person_t *p1, person_t *p2) {
	int com = strcmp(p1->surname, p2->name);
	if(i = com) {
		return i;
	}
	//if(com < 0) {
	//	return 1;
	
	if (i = strcmp(p1->name, p2->name) > 0) {
		return i;
	}
	//if (strcmp(p1->name, p2->name) < 0) {
	//	return 1;
	//}
	i = p1->dob.year - p2->dob.year;
	//same procedure
}
int main() {
	person_t p = { "Joe", "Doe", {3, 12, 2024}};

	person_t *people[100], *ptr;
	people[0] = new_person("Jane", "Doe", 3, 12, 2024);
	
}
