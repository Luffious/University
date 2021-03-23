#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3
#define M 5
#define D 5
#define A -100
#define B 100

int main() {
	srand(time(0));
	char string[] = "Hello";
	char a = 'd';
	int i;
	FILE * file;
	file = fopen("file.txt", "w");
	for(i = 0; i < N; i++){
		fputs(string, file);
		fprintf(file, "\n");
	}
	for(i = 0; i < D; i++){
		fprintf(file, "%5d", A + rand()% (A-B+1));
	}
	fprintf(file, "\n");
	fclose(file);
	file = fopen("file.txt", "a");
	for(i = 0; i < M; i++){
		fprintf(file, "%c ", a);
	}
	fclose(file);
}
