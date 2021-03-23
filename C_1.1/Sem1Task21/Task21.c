#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEFT -100
#define RIGHT 156
#define N 2
#define M 7
#define P 9
int main(void) {
	int i, j;
	srand(time(NULL));
	FILE *output;
	output = fopen("output.txt", "w");
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			int a = LEFT + rand() % RIGHT;
			printf(" %d", a);
			}
	printf("\n");
	}
	int a = LEFT + rand() % RIGHT;
	printf(" %d", a);
	for (i = 0; i < P; i++) {
		int a = LEFT + rand() % RIGHT;
		fprintf(output, "%d\n", a);
	}
fclose(output);
}
