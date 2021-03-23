#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X 1
#define Y 0
#define A 0
#define B 10
#define N 3

void method_euler(double);
void method_euler_mod(double);
void method_euler_improve(double);
void method_runge_kutt(double);
double f(double, double);
double f1(double, double);

int main(void){
	int i;
	double h, step[N] = {0.5, 0.1, 0.01};
	FILE * file;
	file = fopen("file.txt", "w");
	for(i = 0; i < N; i++){
		h = step[i];
		method_euler(h);
		method_euler_mod(h);
		method_euler_improve(h);
		method_runge_kutt(h);
	}
	fclose(file);
}

void method_euler(double h){
	FILE * file;
	file = fopen("file.txt", "a");
	int i, z;
	z = (B - A) / h;
	double x[z + 1], y[z + 1];
	x[0] = X;
	y[0] = Y;
	fprintf(file, "h = %0.2lf\nx =     ", h);
	for(i = 0; i <= z; i++){
		y[i + 1] = y[i] + h * f(x[i], y[i]);
		x[i + 1] = x[i] + h;
	}
	for(i = 0; i <= z; i++){
		fprintf(file, "%0.2lf\t", x[i]);
	}
	fprintf(file, "\ny_e = \t");
	for(i = 0; i <= z; i++){
		fprintf(file, "%0.2lf\t", y[i]);
	}
	fclose(file);
	x[z + 1] = 0;
	y[z + 1] = 0;

}

void method_euler_mod(double h){
	FILE * file;
	file = fopen("file.txt", "a");
	int i, z;
	z = (B - A) / h;
	double x[z + 1], y[z + 1], x1 = 0, y1 = 0;
	x[0] = X;
	y[0] = Y;
	for(i = 0; i <= z; i++){
		x1 = x[i] + h / 2;
		y1 = y[i] + h / 2 * f1(x[i], y[i]);
		y[i + 1] = y[i] + h * f(x1, y1);
		x[i + 1] = x[i] + h;
	}
	fprintf(file, "\ny_em = \t");
	for(i = 0; i <= z; i++){
		fprintf(file, "%0.2lf\t", y[i]);
	}
	fclose(file);
	x[z + 1] = 0;
	y[z + 1] = 0;
}

void method_euler_improve(double h){
	FILE * file;
	file = fopen("file.txt", "a");
	int i, z;
	z = (B - A) / h;
	double x[z + 1], y[z + 1], y1 = 0;
	x[0] = X;
	y[0] = Y;
	for(i = 0; i <= z; i++){
		y1 = y[i] + h * f1(x[i], y[i]);
		x[i + 1] = x[i] + h;
		y[i + 1] = y[i] + h * (f(x[i], y[i]) + f(x[i+1], y1)) / 2;
	}
	fprintf(file, "\ny_ei = \t");
	for(i = 0; i <= z; i++){
		fprintf(file, "%0.2lf\t", y[i]);
	}
	fclose(file);
	x[z + 1] = 0;
	y[z + 1] = 0;
}

void method_runge_kutt(double h){
	FILE * file;
	file = fopen("file.txt", "a");
	int i, z;
	z = (B - A) / h;
	double x[z + 1], y[z + 1], k1, k2, k3, k4;
	x[0] = X;
	y[0] = Y;
	for(i = 0; i <= z; i++){
		k1 = f(x[i], y[i]);
		k2 = f(x[i] + h / 2, y[i] + k1 * h / 2);
		k3 = f(x[i] + h / 2, y[i] + k2 * h / 2);
		k4 = f(x[i] + h, y[i] + h * k3);
		y[i + 1] = y[i] + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		x[i + 1] = x[i] + h;
	}
	fprintf(file, "\ny_rk = \t");
	for(i = 0; i <= z; i++){
		fprintf(file, "%0.2lf\t", y[i]);
	}
	fprintf(file, "\n\n");
	fclose(file);
	x[z + 1] = 0;
	y[z + 1] = 0;
}

double f(double x, double y){
	return (5 + x - (4 * y) / x);
}

double f1(double x, double y){
	return (1 + (4 * y) / pow(x, 2));
}

