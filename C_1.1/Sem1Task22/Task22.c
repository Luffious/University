#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void) {
#define LEFT 10
#define RIGHT 89
#define N 15
#define D 10
srand(time(NULL));
FILE *output;
output = fopen("output.txt", "w");
int i;
for (i = 0; i < N;) {
	int a = LEFT + rand() % RIGHT;
	if ((a / D) + (a % D) < D) {
		fprintf(output, " %8d", a);
		i += 1;
	}
}
fclose(output);
}
