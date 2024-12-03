#include <stdio.h>
struct point {
	int x;
	int y;
};
struct point points[100] = {0};
int main() {
	points[2].x = 10;
	printf("%d\n", points[2]);
}
	
