#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define A 0
#define B 100

int main(){
	srand(time(0));
	int arr[N];
	int i, temp, count = 0;
	for (i = 0; i < N; i++){
		arr[i] = A + rand() % (A - B + 1);
		printf("%5d", arr[i]);
	}
	printf("\n");
	if (arr[0] % 4 == 0){
		temp = arr[1];
		arr[1] = arr[0];
		arr[0] = temp;
		count++;
	}
	for (i = 1; i < N; i++){
		if (count == i){
			i++;
		}
		if (i == 9){
			i++;
		}
		if (arr[i] % 4 == 0){
			temp = arr[i + 1];
			arr[i + 1] = arr[i];
			arr[i] = temp;
			count = i + 1;
		}
	}
	for (i = 0; i < N; i++){
		printf("%5d", arr[i]);
	}
	printf("\n");
}
