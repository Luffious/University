#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_str();
void print_stb();

#define LEFT 0
#define RIGHT 56

int main(){
print_str();
print_stb();
}

void print_str(){
	srand(time(NULL));
	int i, x;
	FILE * output;
	output = fopen("output.txt", "w");
	for (i = 0;i < 15;i++){
		x = LEFT + rand() % RIGHT;
		fprintf(output,"%d ", x);
	}
	fprintf(output,"\n");
	fclose(output);
}

void print_stb(){
	srand(time(NULL));
	int i, x;
	FILE * output;
	output = fopen("output.txt", "a+");
	for (i = 0;i < 9;i++){
		x = LEFT + rand() % RIGHT;
		fprintf(output,"%d\n", x);
	}
	fclose(output);
}

