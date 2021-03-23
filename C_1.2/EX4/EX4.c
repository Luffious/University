#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 11
#define M 11
#define A -25
#define B 85

int main(){
	srand(time(0));
	int i, j, array[N][M] = {{0}}, temp;
	for (i = 0;i < N;i++){
		for (j = 0;j < M;j++){
			array[i][j] = A + rand() % (B - A + 1);
			printf("%d\t", array[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	for (i = 0;i < N;i++){
		for (j = 0;j < M;j++){
			if (i == j){
				temp = array[i][M-1];
				array[i][M-1] = array[i][j];
				array[i][j] = temp;
			}
			printf("%d\t", array[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	for (i = 0;i < N;i++){
		for (j = 0;j < M;j++){
			if (i + j == N - 1){
				temp = array[0][j];
				array[0][j] = array[i][j];
				array[i][j] = temp;
			}
			printf("%d\t", array[i][j]);
		}
		printf("\n");
	}
}
