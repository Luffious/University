#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5
#define M 6

void method_Gauss();
void method_Gauss_Zeidel();
void read_data(double [N][M]);

int main(void){
	method_Gauss();
	method_Gauss_Zeidel();
}

void method_Gauss(){
	FILE * file;
	int i, j, k;
	double a[N][M] = {{0}}, aii, aki, aa, bb, cc, dd, ee;
	file = fopen("answer_data.txt", "w");
	read_data(a);
	for (k = 0; k < M; k++){
		for (i = k; i < N; i++){
			aii = a[i][k];
			for (j = 0; j < M; j++){
				a[i][j] /= aii;
			}
		}
		for (j = 0; j < M; j++){
			aki = a[k][j];
			for (i = k + 1; i < N; i++){
				a[i][j] -= aki;
			}
		}
	}
	ee = a[4][5];
	dd = (a[3][5] - a[3][4] * ee) / a[3][3];
	cc = (a[2][5] - a[2][3] * dd - a[2][4] * ee) / a[2][2];
	bb = (a[1][5] - a[1][2] * cc - a[1][3] * dd - a[1][4] * ee) / a[1][1];
	aa = (a[0][5] - a[0][1] * bb - a[0][2] * cc - a[0][3] * dd - a[0][4] * ee) / a[0][0];
	printf("a = %lf b = %lf c = %lf d = %lf e = %lf\n", aa, bb, cc, dd, ee);
	fprintf(file, "a = %lf b = %lf c = %lf d = %lf e = %lf\n", aa, bb, cc, dd, ee);
	fclose(file);
}

void method_Gauss_Zeidel(){
	FILE * file;
	int i;
	double a[N][M] = {{0}}, old_x[N] = {0}, new_x[N] = {0}, error[N] = {0}, max = -999999999, E = 0.0001;
	file = fopen("answer_data.txt", "a");
	read_data(a);
	while (max < E){
		for (i = 0; i < N; i++){
			old_x[N] = new_x[N];
			new_x[0] = (a[0][5] - a[0][1] * old_x[1] - a[0][2] * old_x[2] - a[0][3] * old_x[3] - a[0][4] * old_x[4]) / a[0][0];
			new_x[1] = (a[1][5] - a[1][0] * new_x[0] - a[1][2] * old_x[2] - a[1][3] * old_x[3] - a[1][4] * old_x[4]) / a[1][1];
			new_x[2] = (a[2][5] - a[2][0] * new_x[0] - a[2][1] * new_x[1] - a[2][3] * old_x[3] - a[2][4] * old_x[4]) / a[2][2];
			new_x[3] = (a[3][5] - a[3][0] * new_x[0] - a[3][1] * new_x[1] - a[3][2] * new_x[2] - a[3][4] * old_x[4]) / a[3][3];
			new_x[4] = (a[4][5] - a[4][0] * new_x[0] - a[4][1] * new_x[1] - a[4][2] * new_x[2] - a[4][3] * new_x[3]) / a[4][4];
			error[i] = fabs((new_x[i] - old_x[i]) / new_x[i]);
			if (error[i] > max){
				max = error[i];
			}
		}
	}
	printf("a = %lf b = %lf c = %lf d = %lf e = %lf\n", new_x[0], new_x[1], new_x[2], new_x[3], new_x[4]);
	fprintf(file, "a = %lf b = %lf c = %lf d = %lf e = %lf\n", new_x[0], new_x[1], new_x[2], new_x[3], new_x[4]);
	for (i = 0; i < N; i++){
		printf("%lf ", error[i]);
	}
	printf("\n");
	fclose(file);
}

void read_data(double a[N][M]){
	FILE * file;
	int i, j;
	if ((file = fopen("input_data.txt", "r")) == 0){
		puts("File does not exist");
		exit(1);
	}
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			fscanf(file, "%lf ", &a[i][j]);
		}
	}
	fclose(file);
}
