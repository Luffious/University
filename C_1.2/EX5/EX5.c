#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 12
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
	for (j = 0;j < N + 1;j++){
		for (i = 1;i < N;i++){
			if (array[i] % 7 == 0){
				temp = array[i];
				array[i] = array[i - 1];
				array[i - 1] = temp;
			}
		}
	}
	for (i = 0;i < N;i++){
		printf("%d ", array[i]);
	}
}
