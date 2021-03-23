#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3
#define M 3
#define A 20
#define E 0.001

int main(){
	double k[N][M], x[A][M], max = 0.0;
	int i, j;
	FILE * file;
	if ((file = fopen("input.txt", "r")) == 0){
		puts("File does not exist");
		exit(1);
	}
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			fscanf(file, "%lf ", &k[i][j]);
		}
	}
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			if (i == 0){
				printf("a%d = %.2lf; \t", j, k[i][j]);
			}
			if (i == 1){
				printf("b%d = %.2lf; \t", j, k[i][j]);
			}
			if (i == 2){
				printf("c%d = %.2lf; \t", j, k[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
	for (j = 0; j < M; j++){
		fscanf(file, "%lf ", &x[0][j]);
	}
	for (i = 1; i < A; i++){
		x[i][0] = (x[i - 1][1] * sin(k[0][2] * x[i - 1][2]) + k[0][0]) / k[0][1];
		x[i][1] = (x[i - 1][2] * sin(k[1][2] * x[i - 1][0]) + k[1][0]) / k[1][1];
		x[i][2] = (x[i - 1][0] * sin(k[2][2] * x[i - 1][1]) + k[2][0]) / k[2][1];
	}
	for (i = 0; i < A; i++){
		for (j = 0; j < M; j++){
			printf("|x[%d] = %.4lf\t|\t", j, x[i][j]);
		}
		if (i > 0){
			for (j = 0; j < M; j++){
				if (x[i][j] - x[i - 1][j] < 0){
					max = (x[i][j] - x[i - 1][j]) * -1;
				}
				else{
					max = x[i][j] - x[i - 1][j];
				}
			}
			printf("|max difference is %.4lf|", max);
		}
		printf("\n");
		if ((max <= E) && (max != 0.0)){
			exit(1);
		}
		max = 0.0;
	}
}
