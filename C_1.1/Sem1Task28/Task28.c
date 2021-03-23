#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define LEFT -12.5
#define RIGHT -6.8
#define STEP 0.5
double function();
double summa();
int main(){
	function();
	summa();
}
double function(double x){
	double y;
	for (x = LEFT;x < RIGHT;x += STEP)
		printf("%lf ", x);
	printf("\n");
	for (x = LEFT;x < RIGHT;x += STEP){
		y = (-8 * pow(x,3)) + (4 * x) - (3 * pow(x,2)) + 4;
		printf("%lf ", y);
	}
	printf("\n");
	return y;
}
double summa(double x, double y, double a){
	a = 0;
	for (x = LEFT;x < RIGHT;x += STEP){
		y = (-8 * pow(x,3)) + (4 * x) - (3 * pow(x,2)) + 4;
		a = a + pow(y,2);
	}
	printf("%lf", a);
	return a;
}

