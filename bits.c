#include<stdio.h>
typedef unsigned u;
struct foo {
	u year	      :11;
	u is_valid    :1;
	u percent     :7;
	unsigned      :0;
	u field1      :3;
	signed field2 :10;
};
int count_bits(int x) {
	int n;
	for (n = 0; x != 0; ++n) {
		x &= (x-1);
	}
	return n;
}
void main() {
	printf("%d\n", count_bits(0xF0));
	struct foo x;
	x.is_valid = 3;
	return;
}