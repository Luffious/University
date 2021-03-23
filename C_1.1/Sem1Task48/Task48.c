#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8
#define M 8
#define A 0
#define B 100

int main(){
	srand(time(0));
	int arr1[N][M];
	int i, j, k, temp;
	printf("Array:\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			arr1[i][j] = A + rand() % (B - A + 1);
			printf("%5d", arr1[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			for (k = 0; k < M - i - 1; k++){
				if(arr1[j][k] > arr1[j][k + 1]) {
					temp = arr1[j][k];
					arr1[j][k] = arr1[j][k + 1] ;
					arr1[j][k + 1] = temp;
				}
			}
		}
	}
	printf("Sorted array:\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			printf("%5d", arr1[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

