#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define A 4
#define B 10.4
#define E 1e-4

void method_right_rectangle();
void method_left_rectangle();
void method_middle_rectangle();
void method_trapeze();
void method_simpson();
double f(double);
int main(void){
method_right_rectangle();
method_left_rectangle();
method_middle_rectangle();
method_trapeze();
method_simpson();
return EXIT_SUCCESS;
}
void method_right_rectangle(){
	int i, n = 10;
	double h, S1, S2;
	do{
		h=(double)(B-A)/n;
		S1=0;
		for(i=0; i < n; i++){
			S1+=h*f(A+(i+1)*h);
		}
		n*=2;
		h=(double)(B-A)/n;
		S2=0;
		for(i=0;i<n;i++){
			S2+= h*f(A+(i+1)*h);
		}
	}while(fabs(S1-S2)>E);
	printf("Right rectangle method: %lf\n", S2);
}
void method_left_rectangle(){
	int i, n = 10;
	double h, S1, S2;
	do{
		h=(double)(B-A)/n;
		S1=0;
		for(i=0; i < n; i++){
			S1+=h*f(A+(i*h));
		}
		n*=2;
		h=(double)(B-A)/n;
		S2=0;
		for(i=0;i<n;i++){
			S2+= h*f(A+(i*h));
		}
	}while(fabs(S1-S2)>E);
	printf("Left rectangle method: %lf\n", S2);
}
void method_middle_rectangle(){
	int i, n = 10;
	double h, S1, S2;
	do{
		h=(double)(B-A)/n;
		S1=0;
		for(i=0; i < n; i++){
			S1+=h*f(A+(i + 1/2)*h);
		}
		n*=2;
		h=(double)(B-A)/n;
		S2=0;
		for(i=0;i<n;i++){
			S2+= h*f(A+(i+1/2)*h);
		}
	}while(fabs(S1-S2)>E);
	printf("Middle rectangle method: %lf\n", S2);
}
void method_trapeze(){
	int i, n = 10;
	double h, S1, S2;
	do{
		h=(double)(B-A)/n;
		S1=0;
		for(i=0; i < n; i++){
			S1+=h*f(A+(i*h))+f(A+(i+1)*h)*(1/2);
		}
		n*=2;
		h=(double)(B-A)/n;
		S2=0;
		for(i=0;i<n;i++){
			S2+= h*f(A+(i*h))+f(A+(i+1)*h)*(1/2);
		}
	}while(fabs(S1-S2)>E);
	printf("Trapeze method: %lf\n", S2);
}
void method_simpson(){
	int i, n = 10;
	double h, S1, S2;
	do{
		h=(double)(B-A)/(2*n);
		S1=0;
		for(i=0; i < n; i++){
			S1+=(h/3)*(f(A+2*i*h)+4*f(A+(2*i+1)*h)+f(A+(2*i+2)*h));
		}
		n*=2;
		h=(double)(B-A)/(2*n);
		S2=0;
		for(i=0;i<n;i++){
			S2+=(h/3)*(f(A+2*i*h)+4*f(A+(2*i+1)*h)+f(A+(2*i+2)*h));
		}
	}while(fabs(S1-S2)>E);
	printf("Simpson method: %lf\n", S2);
}
double f(double x){
	x = sqrt(x - 2);
	return x;
}
