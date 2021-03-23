#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 45
#define M 12
#define L 16
#define A -100
#define B 100

void first();
void second();

int main(){
	first();
	second();
}

void first(){
	int i, array[N] = {0}, count = 0, a = 0;
	for (i = 0;i < N;i++){
		array[i] = A + rand() % (B - A + 1);
		printf("%d ", array[i]);
	}
	printf("\n\n");
	for (i = 0;i < N;i++){
		if(array[i] > 0){
			count++;
		}
	}
	int * new_array;
	new_array = (int*)malloc(count * sizeof(int));
	for (i = 0, a = 0;i < N;i++){
		if (array[i] >= 0){
			new_array[a] = array[i];
			a++;
			printf("%d ", array[i]);
		}
	}
	free(new_array);
	printf("\n\n");
}
void second(){
	int i, j, array[M][L] = {{0}}, count = 0, a = 0, avr = 0;
	for (i = 0;i < M;i++){
		for (j = 0; j < L; j++){
			array[i][j] = A + rand() % (B - A + 1);
			avr += array[i][j];
			printf("%d\t", array[i][j]);
		}
		printf("\n");
	}
	avr /= M*L;
	printf("\n");
	for (i = 0;i < M;i++){
		for (j = 0;j < L;j++){
			if(array[i][j] < avr){
				count++;
			}
		}
	}
	int * new_array;
	new_array = (int*)malloc(count * sizeof(int));
	for (i = 0;i < M;i++){
		for (j = 0, a = 0;j < L;j++){
			if (array[i][j] < avr){
				new_array[a] = array[i][j];
				a++;
				printf("%d ", array[i][j]);
			}
		}
	}
	free(new_array);
	printf("\n");
}
