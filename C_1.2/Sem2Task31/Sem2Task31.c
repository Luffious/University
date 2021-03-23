#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 1000
#define A -25000
#define B 25000

void generation();
void read_file(int [N]);
void method_simple_sort();
void method_puzirek();
void method_comb_sort();

int main(void){
	generation();
	method_simple_sort();
	method_puzirek();
	method_comb_sort();
}

void method_simple_sort(){
	FILE * file;
	time_t start, end;
	start = time(NULL);
	file = fopen("times.txt", "w");
	int a[N] = {0}, i, k, temp, ind_max, max, count = 0;
	read_file(a);
	for (k = 0; k < N - 1; k++){
		max = a[k];
		ind_max = k;
		for (i = k; i < N; i++){
			if (a[i] > max){
				max = a[i];
				ind_max = i;
			}
		}
		temp = a[k];
		a[k] = a[ind_max];
		a[ind_max] = temp;
		if (k != ind_max){
			count++;
		}
	}
	end = time(NULL);
	fprintf(file, "With %d numbers time for simple sort method is %0.10lf and the amount of operations is %d\n", N, difftime(end, start), count);
	fclose(file);
}

void method_puzirek(){
	FILE * file;
	time_t start, end;
	start = time(NULL);
	file = fopen("times.txt", "a");
	int a[N] = {0}, count = 1, i, temp;
	read_file(a);
	long long int count1 = 0;
	while (count > 0) {
		count = 0;
		for (i = 0; i < N - 1; i++){
			if(a[i] < a[i + 1]){
				temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
				count++;
				count1++;
			}
		}
	}
	end = time(NULL);
	fprintf(file, "With %d numbers time for bubble sort method is %0.10lf and the amount of operations is %lli\n", N, difftime(end, start), count1);
	fclose(file);
}

void method_comb_sort() {
	FILE * file;
	time_t start, end;
	start = time(NULL);
	file = fopen("times.txt", "a");
	int a[N] = {0}, i, temp, count = 0;
	read_file(a);
	double fakt = 1.2473309;
	double step = N - 1;
	while (step >= 1){
		for (i = 0; i + step < N; ++i){
			if (a[i] > a[i + (int)step]){
				temp = a[i + (int)step];
				a[i + (int)step] = a[i];
				a[i] = temp;
				count++;
			}
		}
		step /= fakt;
	}
	end = time(NULL);
	fprintf(file, "With %d numbers time for comb sort method is %0.10lf and the amount of operations is %d\n", N, difftime(end, start), count);
	fclose(file);
}

void generation(){
	FILE * file;
	int i;
	srand(time(0));
	file = fopen("input.txt", "w");
	for (i = 0; i < N; i++){
		fprintf(file, "%d ", A + rand() % (B - A + 1));
	}
	fclose(file);
}

void read_file(int a[N]){
	FILE * file;
	int i;
	file = fopen("input.txt", "r");
	for (i = 0; i < N; i++){
		fscanf(file, "%d ", &a[i]);
	}
	fclose(file);
}
