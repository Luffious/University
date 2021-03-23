#include <iostream>
#include <ctime>

#define N 5
#define M 5
#define L 100000
#define A -100
#define B 100

using namespace std;

void Task1(int x[]);
void Task11(int x[]);
void Task12(int x[]);
void Task13(int x[]);
void Task2(int b[N][M]);
void Task3();

int main(){
	srand(time(0));
	int a[N] = {0}, b[N][M]= {{0}};
	int i;
	for (i = 0; i < N; i++){
		a[i] = A + rand() % (B - A + 1);
	}
	Task1(a);
	Task2(b);
	Task3();
}

void Task1(int x[]){
	cout << "Task1" << endl;
	Task11(x);
	Task12(x);
	Task13(x);
}

void Task11(int x[]){
	int c, count = 0, csum = 0, temp;
	int *a = x;
	cout << "Task11" << endl;
	cout << "Input a number in between[-100000; 100000] ";
	cin >> c;
	temp = c;
	while (temp >= 1){
		csum += temp % 10;
		temp /= 10;
	}
	for (a = x; a < &x[N - 1]; a++){
		if (*a > csum){
			count++;
		}
	}
	cout << "Initial data: array" << endl;
	for (a = x; a < &x[N - 1]; a++){
		cout << *a << " ";
	}
	cout <<"\nInteger c - " << c << endl;
	cout << "Result: the sum of the c`s (" << c << ") digits - " << csum << endl;
	cout <<	"And the amount of the elements of the array > then the sum of the c`s - " << count << endl;
}

void Task12(int x[]){
	int max = A + A, temp1 = 0, temp2 = N + 1, count = 0, i;
	long long int multi = 1;
	int *a = x;
	for (i = 0; i < N; i++){
		if (x[i] < 0){
			temp1 = x[i] * -1;
			if ((temp1 != 0) && (temp1 > max) && (temp1 % 3 == 0)){
				if (count == 0){
					max = x[i];
					temp2 = i;
					count++;
				}
			}
		}
		else{
			temp1 = x[i];
			if ((temp1 != 0) && (temp1 > max) && (temp1 % 3 == 0)){
				if (count == 0){
					max = x[i];
					temp2 = i;
					count++;
				}
			}
		}
		i++;
	}
	if ((temp2 == N) && (temp2 == N + 1)){
		multi = 1;
	}
	else{
		for (i = temp2 + 1; i < N; i++){
			multi *= x[i];
		}
	}
	cout << "Task12" << endl;
	cout << "Initial data: array" << endl;
	for (a = x; a < &x[N - 1]; a++){
		cout << *a << " ";
	}
	if (count == 0){
		cout << "\nResult: no max element" << endl;
	}
	else{
		cout << "\nResult: first max element % 3 = 0 is " << max << endl;
		if (multi == 1){
			cout <<"The multiplication of the elements after max can`t be found (because max was the last element or there was no max)" << endl;
		}
		else{
			cout <<"And the multiplication of the elements after max is - " << multi << endl;
		}
	}

}

void Task13(int x[]){
	int i, count = 1, temp, temp1, csum, csum1;
	cout << "Task13" << endl;
	cout << "Initial data: array" << endl;
	for (i = 0; i < N; i++){
		cout << x[i] << " ";
	}
	while (count > 0) {
		count = 0;
		for (i = 0; i < N - 1; i++){
			if(x[i] > x[i + 1]){
				temp = x[i];
				x[i] = x[i + 1];
				x[i + 1] = temp;
				count++;
			}
		}
	}
	count = 1;
	while (count > 0) {
		count = 0;
		for (i = 0; i < N - 1; i++){
			temp1 = -1 * x[i];
			while (temp1 >= 1){
				csum += temp1 % 10;
				temp1 /= 10;
			}
			temp1 = -1 * x[i + 1];
			while (temp1 >= 1){
				csum1 += temp1 % 10;
				temp1 /= 10;
			}
			if((x[i] < 0) && (x[i + 1] < 0) && (csum < csum1)){
				temp = x[i];
				x[i] = x[i + 1];
				x[i + 1] = temp;
				count++;
			}
			csum = 0;
			csum1 = 0;
		}
	}
	count = 1;
	while (count > 0) {
		count = 0;
		for (i = 0; i < N - 1; i++){
			temp1 = x[i];
			while (temp1 >= 1){
				csum += temp1 % 10;
				temp1 /= 10;
			}
			temp1 = x[i + 1];
			while (temp1 >= 1){
				csum1 += temp1 % 10;
				temp1 /= 10;
			}
			if ((x[i] >= 0) && (x[i + 1] >= 0) && (csum > csum1)){
				temp = x[i];
				x[i] = x[i + 1];
				x[i + 1] = temp;
				count++;
			}
			csum = 0;
			csum1 = 0;
		}
	}
	cout << "\nResult: new array" << endl;
	for (i = 0; i < N; i++){
		cout << x[i] << " ";
	}
}

void Task2(int b[N][M]){
	cout << "\n\nTask2" << endl;
	srand(time(0));
	int i = 0, j = 0, count = 0, count1 = 1;
	while (j != M - 1){
		if ((i == 0) && (j == 0)){
			b[i][j] = A + rand() % (B - A + 1);
			cout << b[i][j] << " ";
			j++;
			b[i][j] = A + rand() % (B - A + 1);
			cout << b[i][j] << endl;
		}
		if (i == 0){
			if (count == 0){
				while (j != 0){
					i++;
					j--;
					b[i][j] = A + rand() % (B - A + 1);
					cout << b[i][j] << " ";
					count++;
				}
			}
			else{
				if (count > 0){
					j++;
					b[i][j] = A + rand() % (B - A + 1);
					cout << b[i][j] << endl;
					count = 0;
				}
				cout << endl;
			}
		}
		if (j == 0){
			if (count1 > 0){
				i++;
				b[i][j] = A + rand() % (B - A + 1);
				cout << b[i][j] << endl;
				count1 = 0;
			}
			else{
				if (count1 == 0){
					while (i != 0){
						i--;
						j++;
						b[i][j] = A + rand() % (B - A + 1);
						cout << b[i][j] << " ";
						count1++;
					}
					cout << endl;
				}
			}
		}
	}
	count = 1;
	count1 = 1;
	while (i != N && j != M){
		if (j == M - 1){
			if (count1 > 0){
				i++;
				b[i][j] = A + rand() % (B - A + 1);
				cout << b[i][j] << endl;
				count1 = 0;
			}
			else{
				if (count1 == 0){
					while (i != N - 1){
						i++;
						j--;
						b[i][j] = A + rand() % (B - A + 1);
						cout << b[i][j] << " ";
						count1++;
					}
					cout << endl;
				}
			}
		}
		if (i == N - 1){
			if (count == 0){
				while (j != M - 1){
					i--;
					j++;
					b[i][j] = A + rand() % (B - A + 1);
					cout << b[i][j] << " ";
					count++;
				}
			}
			else{
				if (count > 0){
					j++;
					b[i][j] = A + rand() % (B - A + 1);
					cout << b[i][j] << endl;
					count = 0;
				}
				cout << endl;
			}
		}
	}
	cout << "\n\n";
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			cout << b[i][j] << " ";
		}
		cout << endl;
	}
}

void Task3(){
	 int count = 0, i, temp;
	 for (i = 0; i < L; i++){
		 temp = i;
		 while (temp >= 4){
			 if (temp % 10 == 4 || temp % 100 == 13){
				 count++;
				 break;
			 }
	     temp /= 10;
		 }
	 }
	 cout << "\n\nTask3" << endl;
	 cout << "You need to exclude " << count << " numbers" << endl;
}
