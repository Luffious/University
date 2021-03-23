#include <stdio.h>
#include <stdlib.h>

int main() {
	int a, b;
	a = 1;
	while (a >= 0) {
		scanf("%d", &a);
	}
	if (a < 0) {
		while (a < 0) {
			b = a + 7;
			printf("%d + 7 = %d\n", a, b);
			a = b;
		}
	}
}
