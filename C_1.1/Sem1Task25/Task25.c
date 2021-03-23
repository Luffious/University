#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int main() {
#define LEFT -12.5
#define RIGHT -6.8
#define STEP 0.5
double a = 0,x,y;
for (x = LEFT;x < RIGHT;x += STEP){
	y = (-8 * pow(x,3)) + (4 * x) - (3 * pow(x,2)) + 4;
	printf("%lf\n", x);
	printf("%lf", y);
	a = a + pow(y,2);
}
printf("%lf", a);
}
