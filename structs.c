#include<stdio.h>
struct point {
	int x;
	int y;
} p;

int main() {
	p.x = 10;
	p.y = 20;
	printf("x= %d, y= %d\n", p.x, p.y);
}
