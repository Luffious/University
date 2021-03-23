#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define M 7
#define A -100
#define B 100

int main(){
	srand(time(0));
	int a[N][M], asum[M];
	int sum = 0, i, j, max = A * 10, b, c = 0;
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			a[i][j] = A + rand() % (B - A + 1);
			printf("%5d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (j = 0, b = 0; j < M; j++){
		for (i = 0; i < N; i++){
			if ((a[i][j] % 7 == 0) && (a[i][j] < 0)){
				sum += a[i][j];
				asum[b] = sum;
			}
		}
		if ((sum > max) && (sum != 0)){
			printf("Sum of %d table is %d\n", j + 1, asum[b]);
			c = j + 1;
			max = sum;
		}
		sum = 0;
	}
	if (c == 0){
		printf("\nNo such table");
	}
	else{
		printf("\nNumber of the table is %d", c);
	}
}
