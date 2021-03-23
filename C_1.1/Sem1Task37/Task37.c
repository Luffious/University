#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3
#define A -99
#define B 99

int maximal(int a[N]);
int amount_div_by_nine(int a[N]);
int sum_elem_higher_rand(int a[N]);

int main() {
	srand(time(0));
	int i, j, k, l;
	int a[N];
	FILE*file;
	file = fopen("temp.txt", "w");
	for(i=0;i<N;i++){
		a[i] = A + rand() % (B-A+1);
		printf("%d ", a[i]);
		fprintf(file, "%d ", a[i]);
	}
	fclose(file);
	j = maximal(a);
	k = amount_div_by_nine(a);
	l = sum_elem_higher_rand(a);
	printf("\n");
	if (j < 0){
		printf("No index of the maximal array element\n");
	}
	else{
		printf("Index of the maximal array element is %d\n", j);
	}
	if (k == 0){
		printf("No elements dividable by nine\n");
	}
	else{
		printf("The amount of elements dividable by nine is/are %d\n", k);
	}
	if (l == 0){
		printf("No summary of last elements's (which are higher than random integer) digits or it's equal to 0\n");
	}
	else{
		printf("The summary of last elements's (which are higher than random integer) digits is %d\n", l);
	}
}
int maximal(int a[N]){
	int i, j = -1, max = a[0];
	for(i=0,j=0;i<N;i++){
		if (a[i] > max){
			max = a[i];
			j = i;
		}
	}
	return j;
}
int amount_div_by_nine(int a[N]){
	int i, count = 0;
	for(i=0;i<N;i++){
		if (a[i] % 9 == 0)
			count++;
	}
	return count;
}
int sum_elem_higher_rand(int a[N]){
	int i, c, b, sum = 0;
	c = A/3 + rand() % ((B/3)-(A/3)+1);
	for(i=0;i<N;i++){
		if (a[i] > c){
			b = a[i] % 10;
			sum += b;
		}
	}
	printf("\n    %d  %d", c, sum);
	return sum;
}
