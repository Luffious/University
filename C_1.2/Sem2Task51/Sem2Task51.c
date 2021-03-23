#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define M 9

void method_mnk();
void read_mass(double x[M], double y[M]);
void read_matrix (double m[M][N]);
void method_Gauss();

int main(void) {
	method_mnk();
	method_Gauss();
}

void read_mass(double x[M], double y[M]){
	FILE * file;
	int i;
	file = fopen ("input_data.txt", "r");
	for (i = 0; i < M; i++){
		fscanf (file, "%lf", &x[i]);
	}
	for (i = 0; i < M; i++){
		fscanf (file, "%lf", &y[i]);
	}
	fclose (file);
}

void read_matrix (double m[M][N]){
	FILE * file;
	int i,j;
	file = fopen ("input_data1.txt", "r");
	for (i = 0; i < M; i++){
		for (j = 0; j < N; j++){
			fscanf (file, "%lf", &m[i][j]);
		}
	}
}

void method_mnk(){
	double x[M], y[M];
	read_mass(x, y);
	int i, j;
	printf ("x =\n");
	for (i = 0; i < M; i++){
		printf ("| %0.2lf ", x[i]);
	}
	printf ("|\ny =\n");
	for (i = 0; i < M; i++){
		printf ("| %0.2lf ", y[i]);
	}
	double S[M] = {0}, Sy [M] = {0};
	for (i = 0; i < M; i++){
		for (j = 0; j < M; j++){
			S[i] += pow(x[j], i + 1);
		}
	}
	for (i = 0; i < M; i++){
		for (j = 0; j < M; j++){
			Sy[i] += y[j] * pow(x[j], i);
		}
	}
	printf ("|\nS =\n");
	for (i = 0; i < M; i++){
		printf ("| %0.5lf ", S[i]);
	}
	printf ("|\nSy =\n");
	for (i = 0; i < M; i++){
		printf ("| %0.5lf ", Sy[i]);
	}
	double a[M][N];
	a[0][0] = N;
	for (j = 1; j < N; j++)
		a[0][j] = S[j-1];
	for(i = 1; i < M; i++){
		for(j = 0; j < N; j++)
			a[i][j] = S[i + j - 1];
	}
	for(i = 0; i < M; i++){
		a[i][M] = Sy[i];
	}
	FILE * file;
	file = fopen ("input_data1.txt","w");
	for(i = 0; i < M; i++){
		for(j = 0; j < N; j++){
			fprintf(file, "%-20.5lf", a[i][j]);
		}
		fprintf(file, "\n");
	}
	fclose (file);
}

void method_Gauss(){
	double m[M][N];
	read_matrix(m);
	double x[M],  k, g;
	int i, j, l;
	for (l = 0; l < M; l++) {
		for (j = l; j < M - 1; j++) {
			g = m[l][l] / m[j + 1][l] * (-1);
			for (i = l; i < N; i++) {
				k = m[l][i];
				k /= g;
				m[j + 1][i] += k;
			}
		}
	}
	for (l = M - 1; l > 0; l--) {
		for (j = l; j >= 0; j--) {
			g = m[l][l] / m[j - 1][l] * (-1);
			for (i = M; i >= 0; i--) {
				k = m[l][i];
				k /= g;
				m[j - 1][i] += k;
			}
		}
	}
	for (i = 0; i < M; i++){
		x[i] = m[i][M] / m[i][i];
	}
	read_matrix(m);
	printf ("|\nAnswer =\n");
	for (i = 0; i < M; i++){
		printf ("| x(%d) = %lf ", i, x[i]);
	}
	double S[M], Sy[M], R, rez = 0;
	read_mass(S, Sy);
	for (i = 0; i < M; i++){
		R += Sy[i] - x[0] - x[1]*S[i] - x[2]*pow(S[i],2) - x[3]*pow(S[i],3) - x[4]*pow(S[i],4) - x[5]*pow(S[i],5);
	}
	R *= R;
	for (i = 0; i < M; i++){
		rez += x[0] + x[1]*S[i] + x[2]*pow(S[i],2) + x[3]*pow(S[i],3) + x[4]*pow(S[i],4) + x[5]*pow(S[i],5);
	}
	printf("|\nResult = \n| %lf ", rez);
	printf("|\nR = \n| %lf ", R);
	printf ("|\nY =\n| ");
	for (i = 0; i < M; i++){
		printf ("%lf | ", x[0] + x[1]*S[i] + x[2]*pow(S[i],2) + x[3]*pow(S[i],3) + x[4]*pow(S[i],4) + x[5]*pow(S[i],5));
	}
}
