#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 8
#define A -34
#define B 48

void make_arr();
void input_arr();
double avr_elem_in_arr();
int max_elem_main_diag();

int main(){
	make_arr();
	input_arr();
	printf("%0.2lf", avr_elem_in_arr()*max_elem_main_diag());
}
void make_arr(){
	srand(time(0));
	int i, j, arr[N][N];
	for (i = 0;i < N; i++){
		for (j = 0;j < N;j++){
			arr[i][j] = A + rand() % (B - A + 1);
		}
	}
}
void input_arr(){
	int i, j, arr[N][N];
	for (i = 0;i < N; i++){
		for (j = 0;j < N;j++){
			printf("%d\t", arr[i][j]);
		}
	printf("\n");
	}
}
double avr_elem_in_arr(){
	int i, j, arr[N][N];
	double avr = 0;
	for (i = 0;i < N; i++){
		for (j = 0;j < N;j++){
			avr += arr[i][j];
		}
	}
	avr /= pow(N,2);
	return avr;
}
int max_elem_main_diag(){
	int i, j, arr[N][N], max = arr[0][0];
	for (i = 0;i < N; i++){
		for (j = 0;j < N;j++){
			if ((i = j) && (arr[i][j] > max))
				max = arr[i][j];
		}
	}
	return max;
}
