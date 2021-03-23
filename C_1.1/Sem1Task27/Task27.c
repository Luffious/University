#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
double calculation();
int main(){
	double a, b;
	FILE * input;
	input = fopen("input.txt", "r");
	if (input == 0)
		puts("File doesn`t exist");
	else
		puts("File exist");
	fscanf(input, "%lf %lf", &a, &b);
	double c = calculation(a, b);
	if (c == 0)
		printf("No answer");
	else
		printf("The answer is %lf", c);
	fclose(input);
}
double calculation(double a, double b){
	double c;
	if (((cos(0.5 * (a + b))) > 1) || ((cos(0.5 * (a + b))) < 0) || ((cos(0.5 * (a - b))) > 1) || ((cos(0.5 * (a - b))) < 0)){
		printf("Impossible\n");
		return (0);
	}
	else {
		c = (2 * cos((a + b) * 0.5) * cos((a - b) * 0.5));
		return c;
	}
}
