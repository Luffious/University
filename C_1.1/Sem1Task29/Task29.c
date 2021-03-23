#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
#define M 30
int main(){
	int i, a;
	char arr[N][M];
	for (i = 0; i < N; i++)
		gets(arr[i]);
	for (i = 0; i < N; i++) {
		a = strlen(arr[i]);
		if ((arr[i][a-2] == 'a') || (arr[i][a-2] == 'e') || (arr[i][a-2] == 'i') || (arr[i][a-2] == 'o') || (arr[i][a-2] == 'u') || (arr[i][a-2] == 'y'))
			puts(arr[i]);
	}
}

