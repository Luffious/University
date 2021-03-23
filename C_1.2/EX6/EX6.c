#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20
#define A -50
#define B 50

int main(){
	srand(time(0));
	int i, j, array[N] = {0}, temp;
	for (i = 0;i < N;i++){
		array[i] = A + rand() % (B - A + 1);
		printf("%d ", array[i]);
	}
	printf("\n\n");
	for (i = N / 2 + 1;i < N - 1;i++){
		for (j = N / 2;j < N - 1;j++){
			if (array[j] <  array[j+1]){
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
	for (i = 0;i < N;i++){
		printf("%d ", array[i]);
	}
}
