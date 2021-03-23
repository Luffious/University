#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3
#define M 3
#define A -100
#define B 100

void first();
void second();

int main(){
	first();
	second();
}

void first(){
	srand(time(0));
	int array[N];
	int i, a, count = 0;
	FILE*file;
	file = fopen("temp.txt", "w");
	for(i=0;i<N;i++){
		array[i] = A + rand() % (B-A+1);
		if ((array[i] % 2 != 0) && (array[i] < 0))
			count++;
		fprintf(file, "%d\t", array[i]);
		printf("%d\t", array[i]);
	}
	printf("\n\n");
	int * new_array = (int*)malloc(count * sizeof(int));
	for (i = 0, a = 0;i < N;i++){
		if ((array[i] % 2 != 0) && (array[i] < 0)){
			new_array[a] = array[i];
			a++;
			printf("%d\t", array[i]);
		}
	}
	free(new_array);
	printf("\n\n");
	fclose(file);
}
void second(){
	srand(time(0));
	int array[N][M];
	int i, j, a, count = 0;
	FILE*file;
	file = fopen("temp.txt", "w");
	for(i=0;i<N;i++){
		for (j = 0;j < M;j++){
			array[i][j] = A + rand() % (B-A+1);
			fprintf(file, "%d\t", array[i][j]);
			printf("%d\t", array[i][j]);
			if ((array[i][j] % 3 == 0) && (j > i) && (j + i < N))
				count++;
		}
		fprintf(file, "\n");
		printf("\n");
	}
	printf("\n\n");
	int * new_array = (int*)malloc(count * sizeof(int));
	for (i = 0;i < N;i++){
		for (j = 0, a = 0;j < N;j++){
			if ((array[i][j] % 3 == 0) && (j > i) && (j + i > N)){
				new_array[a] = array[i][j];
				a++;
				printf("%d\t", array[i][j]);
			}
		}
	}
	free(new_array);
	fclose(file);
	printf("\n\n");
}
