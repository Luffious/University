#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8
#define A 0
#define B 100

int main(){
	srand(time(0));
	int arr1[N], arr2[N], arr3[N + N];
	int i, j, temp, a;
	printf("First array:\n");
	for (i = 0; i < N; i++){
		arr1[i] = A + rand() % (B - A + 1);
		arr2[i] = A + rand() % (B - A + 1);
		printf("%5d", arr1[i]);
	}
	printf("\n\n");
	printf("Second array:\n");
	for (i = 0; i < N; i++){
		printf("%5d", arr2[i]);
	}
	printf("\n\n");
	for (i = 0; i < N - 1; i++){
		for (j = 0; j < N - i - 1; j++){
			if(arr1[j] < arr1[j + 1]) {
				temp = arr1[j];
				arr1[j] = arr1[j+1] ;
			    arr1[j+1] = temp;
			}
		}
	}
	for (i = 0; i < N - 1; i++){
		for (j = 0; j < N - i - 1; j++){
			if(arr2[j] > arr2[j + 1]) {
				temp = arr2[j];
				arr2[j] = arr2[j+1] ;
				arr2[j+1] = temp;
			}
		}
	}
	for (i = 0; i < N / 2; i++){
		arr3[i] = arr1[i];
	}
	for (i = N / 2, a = 0; (i < N + N / 2) && (a < N); i++, a++){
		arr3[i] = arr2[a];
	}
	for (i = N + N / 2, a = N / 2; (i < N + N) && (a < N); i++, a++){
		arr3[i] = arr1[a];
	}
	printf("Sorted first array:\n");
	for (i = 0; i < N; i++){
		printf("%5d", arr1[i]);
	}
	printf("\n\n");
	printf("Sorted second array:\n");
	for (i = 0; i < N; i++){
		printf("%5d", arr2[i]);
	}
	printf("\n\n");
	printf("Combined array:\n");
	for (i = 0; i < N + N; i++){
		printf("%5d", arr3[i]);
	}
	printf("\n\n");
}
