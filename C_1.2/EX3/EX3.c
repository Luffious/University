#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 7
#define M 9
#define A -100
#define B 100

int main(){
	srand(time(0));
	int i, j, array[N][M] = {{0}}, min, max, a;
	FILE*file;
	file = fopen("output.txt", "w");
	for (i = 0;i < N;i++){
		for (j = 0;j < M;j++){
			array[i][j] = A + rand() % (B - A + 1);
			fprintf(file, "%d\t", array[i][j]);
		}
		fprintf(file, "\n");
	}
	fprintf(file, "\n\n");
	min = array[0][0];
	max = A - 1;
	fclose(file);
	file = fopen("output.txt", "a");
	int new_array[N];
	for (i = 0, a = 0;i < N;i++){
		for (j = 0;j < M;j++){
			if (array[i][j] < min){
				min = array[i][j];
				new_array[a] = min;
			}
		}
		if (min > max)
			max = min;
		fprintf(file, "%d ", min);
		min = array[0][0];
	}
	fprintf(file, "\n\n%d\n", max);
}
