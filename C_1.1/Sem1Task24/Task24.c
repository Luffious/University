#include <stdio.h>
#include <stdlib.h>
int main() {
int a, b = 1, i;
for (i = 0;i < 10;){
	scanf("%d", &a);
	while (a > 0 ){
		b = b * (a % 10);
		a /= 10;
	}
	printf("%d\n", b);
	b = 1;
	i += 1;
}
}

