#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 5
#define A -99
#define B 99

int main() {
	srand(time(0));
	int init_array[N][N];
	int new_array[N][N];
	int i, j, min = B + 1, count = 0, count1 = 0;
	double temp = 0;
	FILE*file;
	file = fopen("array.txt", "w");
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			init_array[i][j] = A + rand() % (B - A + 1);
			fprintf(file, "%5d ", init_array[i][j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
	FILE*arr;
	if ((arr = fopen("array.txt", "r")) == 0){
		puts("File does not exist");
		exit(1);
	}
	arr = fopen("array.txt", "r");
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			fscanf(arr, "%d\t", &new_array[i][j]);
			if((i + j < N - 1) && (new_array[i][j] > 0))
				count++;
			if ((i > N / 2) && (new_array[i][j] < min))
				min = new_array[i][j];
			if ((i < N / 2) && (new_array[i][j] % 2 == 0)){
				count1++;
				temp += new_array[i][j];
			}
		}
	}
	if (count == 0){
		printf("No count, ");
	}
	else{
		printf("Count = %d, ", count);
	}
	if (min > B){
		printf("no min, ");
	}
	else{
		printf("min = %d, ", min);
	}
	if (temp == 0){
		printf("no temp.\n");
	}
	else{
		temp /= count1;
		printf("temp = %0.1lf.\n", temp);
	}
	fclose(file);
}
