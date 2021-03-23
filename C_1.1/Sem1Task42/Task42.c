#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define M 10
#define A -100
#define B 100


int main(){
	srand(time(0));
	int array[N][M], string[N], raw[M];
	int i, j, a = 0, count = 0, min, count1 = 0;
	for (i = 0; i < N; i++, a++){
		for (j = 0; j < M; j++){
			array[i][j] = A + rand() % (B - A + 1);
			printf("%5d", array[i][j]);
			if ((array[i][j] % 14 == 0)){
				count++;
			}
		}
		string[a] = count;
		printf("   |%d\n", string[a]);
		count = 0;
	}
	min = array[0][0];
	printf("-----------------------------------------------------\n");
	for (j = 0; j < M; j++){
		for (i = 0; i < N; i++){
			if ((array[i][j] > 0) && (array[i][j]) < 10){
				if ((array[i][j] == 4) && (array[i][j] < min)){
					raw[j] = array[i][j];
					count1++;
				}
			}
			else if (array[i][j] >= 10){
				if (((array[i][j] % 10) + (array[i][j] / 10) == 4) && (array[i][j] < min)){
					raw[j] = array[i][j];
					count1++;
				}
			}
		}
		if (count1 > 0){
			printf("%5d", raw[j]);
			count1 = 0;
		}
		else{
			printf(" NSEF");
		}
	}

}
