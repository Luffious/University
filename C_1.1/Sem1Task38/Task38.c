#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 9
#define A -99.5
#define B 99.5

int neg_lines(double array[N][N]);
double max_elem_main_diag(double array[N][N]);
int sum_elem_with_null_body(double array[N][N]);


int main() {
	srand(time(0));
	double array[N][N];
	double l;
	int i, j, k, m;
	FILE*file;
	file = fopen("temp.txt", "w");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			 array[i][j] = A + (double) rand() / RAND_MAX * (B - A + 1);
			fprintf(file, "%7.2lf\t", array[i][j]);
		}
		fprintf(file, "\n");
	}
	k = neg_lines(array);
	l = max_elem_main_diag(array);
	m = sum_elem_with_null_body(array);
	if (k == 0){
		printf("No lines with negative integers");
	}
	else{
		printf("The amount of lines with negative integers is/are %d\n", k);
	}
	printf("The highest element of main diagonal is %0.2lf\n", l);
	if (m == 0){
		printf("No elements with 0. or it is/they are all 0");
	}
	else{
		printf("Sum of the absolute elements with 0. is %d\n", m);
	}
}
int neg_lines(double array[N][N]){
	int i, j, count = 0, count1 = 0;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%7.2lf\t", array[i][j]);
			if (array[i][j] < 0){
				count++;
			}
		}
		printf("       %d", count);
		if (count>0){
			count1++;
			count = 0;
		}
		printf("\n");
	}
	return count1;
}
double max_elem_main_diag(double array[N][N]){
	int i, j;
	double max = array[0][0];
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if (i == j){
				max = (array[i][j] > max) ? array[i][j] : max;
			}
		}
	}
	return max;
}
int sum_elem_with_null_body(double array[N][N]){
	int i, sum = 0, j, a;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if ((array[i][j] < 1) && (array[i][j] > -1)){
				if ((array[i][j] < 1) && (array[i][j] >= 0)) {
					a = array[i][j] * 100;
				}
				else if ((array[i][j] > -1) && (array[i][j] < 0)){
					a = array[i][j] * -100;
				}
				sum += a;
				printf("\n%5.2lf      %d      %d\n", array[i][j], a, sum);
			}
		}
	}
	return sum;
}

