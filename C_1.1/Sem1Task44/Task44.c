#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8
#define A 0
#define B 100

int main(){
	srand(time(0));
	int a[N][N];
	int i, j, temp, min = B + 1, imin, jmin;
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			a[i][j] = A + rand() % (B - A + 1);
			printf("%5d", a[i][j]);
		}
		printf("\n");
	}
	for (i = 0; i < N; i++){
		temp = a[i][2];
		a[i][2] = a[i][N/2];
		a[i][N/2] = temp;
	}
	printf("\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%5d", a[i][j]);
		}
		printf("\n");
	}
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			if ((a[i][j] < min) && (a[i][j] % 7 == 0)){
				min = a[i][j];
				imin = i;
				jmin = j;
			}
		}
	}
	printf("\nMin is %d\n\n", min);
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			temp = a[imin][j];
			a[imin][j] = a[i][jmin];
			a[i][jmin] = temp;
		}
	}
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%5d", a[i][j]);
		}
		printf("\n");
	}
}
