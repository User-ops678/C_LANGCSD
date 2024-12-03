#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 100000

void print_array(int *, int);


void swap(int *x, int *y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

void bubblesort(int *a, int size) {
  int i, j;

  for(j = 0; j < size; j++) {
    for(i = 0; i < size - 1; i++) {
      if(a[i] > a[i+1]) swap(&a[i], &a[i+1]);
    }
  }
}

void quicksort(int *a, int size) {
  int left = 1, right = size-1;
  int pivot = size/2;

  if(size <= 1) return;

  swap(&a[0], &a[pivot]);

  while(left <= right) {
    if(a[left] < a[0]) left++;
    else swap(&a[left], &a[right--]);
  }
  swap(&a[0], &a[left-1]);

  quicksort(a, left-1);
  quicksort(&a[left], size - left);
}

void print_array(int *a, int size) {
  int i;

  for(i = 0; i < size; i++) {
    printf("%3d%c", a[i], (i+1)%10?' ':'\n');
  }
  printf("\n");
}

int main() {
  int *Array = malloc(N*sizeof(int));
  int i;

  srand(time(0));

  for(i = 0; i < N; i++) {
    Array[i] = rand() % N;
  }

  /*
  print_array(Array, N);
  printf("\n----\n");
  */
  quicksort(Array, N);
  /*bubblesort(Array, N);*/
  /*
  print_array(Array, N);
  printf("\n");
  */
}

