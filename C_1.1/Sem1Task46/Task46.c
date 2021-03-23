#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6
#define M 8
#define A 0
#define B 100

void first(int arr[N]);
void second(int arr1[N][M]);

int main(){
	srand(time(0));
	int arr[N], arr1[N][M];
	int i, j;
	for (i = 0; i < N; i++){
		arr[i] = A + rand() % (A - B + 1);
	}
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			arr1[i][j] = A + rand() % (A - B + 1);
		}
	}
	first(arr);
	second(arr1);
}

void first(int arr[N]){
	int i, max, a, temp, b;
	max = arr[0];
	for (i = 0; i < N; i++){
		printf("%5d", arr[i]);
		if (arr[i] > max){
			max = arr[i];
			a = i;
		}
	}
	printf("\n\nSpot of max is %d\n\n", a + 1);
	if (((N - a - 1) % 2 == 0) && (N - a - 1 != 0)){
		for (i = a + 1, b = 1; i < (a + 1 + N) / 2; i++, b++){
			temp = arr[i];
			arr[i] = arr[N - b];
			arr[N - b] = temp;
		}
	}
	else if (((N - a - 1) % 2 != 0) && (N - a - 1 != 1)){
		for (i = a + 1, b = 1; i < (a + 1 + N) / 2; i++, b++){
			temp = arr[i];
			arr[i] = arr[N - b];
			arr[N - b] = temp;
		}
	}
	for (i = 0; i < N; i++){
		printf("%5d", arr[i]);
	}
	printf("\n\n");
}

void second(int arr1[N][M]){
	int i, j, temp;
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			printf("%5d", arr1[i][j]);
		}
		printf("\n");
	}
	for (i = 0; i < N; i++){
		for (j = 0; j < M - 3; j++){
			temp = arr1[i][j];
			arr1[i][j] = arr1[i][j + 3];
			arr1[i][j + 3] = temp;
		}
	}
	for (i = 0; i < N; i++){
		temp = arr1[i][5];
		arr1[i][5] = arr1[i][6];
		arr1[i][6] = arr1[i][7];
		arr1[i][7] = arr1[i][5];
		arr1[i][5] = temp;
	}
	for (i = 0; i < N; i++){
		temp = arr1[i][5];
		arr1[i][5] = arr1[i][6];
		arr1[i][6] = temp;
	}
	printf("\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			printf("%5d", arr1[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
