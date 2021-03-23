#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define A -99
#define B 99

int main(void) {
	srand(time(0));
	int a[N];
	int i, min = B + 1, max = A - 1, pos = 0, count = 0, b, count1 = 0;
	FILE*file;
	if ((file = fopen("output.txt", "w")) == 0){
		puts("File does not exist");
		exit(1);
	}
	file = fopen("output.txt", "w");
	for(i=0;i<N;i++){
		a[i] = A + rand() % (B-A+1);
		fprintf(file, "%d ", a[i]);
		if(a[i]>0){
			pos += a[i];
			count++;
		}
		if(a[i]%3==0){
			min = (a[i] < min) ? a[i] : min;
		}
		if(a[i]%2==0){
			max = (a[i] > max) ? a[i] : max;
		}
	}
		if (max < A){
			fprintf(file, "\nNo max, ");
		}
		else{
			fprintf(file, "\nMax = %d, ", max);
			count1++;
		}
		if (min > B){
			fprintf(file, "no min, ");
		}
		else{
			fprintf(file, "min = %d, ", min);
			count1++;
		}
		if (pos == 0){
			fprintf(file, "no pos, ");
		}
		else{
			fprintf(file, "pos = %d, ", pos);
			count1++;
		}
		if (count == 0){
			fprintf(file, "no count.\n");
		}
		else{
			fprintf(file, "count = %d.\n", count);
			count1++;
		}
	if (count1 == 4){
		b = max*min*pos/count;
		fprintf(file, "b = max*min*pos/count = %d\n", b);
	}
	else{
		fprintf(file, "Can't get special integer\n");
	}
	fclose(file);
	return EXIT_SUCCESS;
}
