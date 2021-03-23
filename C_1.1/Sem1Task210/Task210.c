#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 100
#define N 3
int main(){
	char s1[M], s2[M], s3[M];
	gets(s1);
	puts(s1);
	gets(s2);
	puts(s2);
	gets(s3);
	puts(s3);
	puts(strcat(s1, s2));
	puts(strcat(s1, s3));
}

