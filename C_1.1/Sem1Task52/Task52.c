#include <stdio.h>
#include <stdlib.h>

#define N 40

int main(void) {
	int i = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	char letter = 0, string1[N], string2[N], string3[N], string4[N];
	FILE * file;
	file = fopen("file.txt", "r");
	if (file == 0){
		printf("Error");
		exit(0);
	}
	while ((letter = fgetc(file)) != EOF){
		putchar(letter);
	}
	printf("\n");
	fclose(file);
	file = fopen("file.txt", "r");
	while ((letter = fgetc(file)) != '\0'){
		string1[i] = letter;
		c1++;
		i++;
		putchar(letter);
	}
	while ((letter = fgetc(file)) != '\0'){
		string2[i] = letter;
		c2++;
		i++;
		putchar(letter);
	}
	while ((letter = fgetc(file)) != '\0'){
		string3[i] = letter;
		c3++;
		i++;
		putchar(letter);
	}
	while ((letter = fgetc(file)) != '\0'){
		string4[i] = letter;
		c4++;
		i++;
		putchar(letter);
	}
	/*putchar(string1[0]);
	for (i = 0; i < c1; i++){
		if (string1[i] == ' '){
			putchar(string1[i - 1]);
			putchar(string1[i + 1]);
		}
	}
	putchar(string1[c1]);
	putchar(string2[0]);
	for (i = 0; i < c2; i++){
		if (string2[i] == ' '){
			putchar(string2[i - 1]);
			putchar(string2[i + 1]);
		}
	}
	putchar(string2[c2]);
	putchar(string3[0]);
	for (i = 0; i < c3; i++){
		if (string3[i] == ' '){
			putchar(string3[i - 1]);
			putchar(string3[i + 1]);
		}
	}
	putchar(string3[c3]);
	putchar(string4[0]);
	for (i = 0; i < c4; i++){
		if (string4[i] == ' '){
			putchar(string4[i - 1]);
			putchar(string4[i + 1]);
		}
	}
	putchar(string4[c4]);*/
	fclose(file);
}

