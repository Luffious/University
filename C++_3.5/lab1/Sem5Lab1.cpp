#include <iostream>
#include <ctime>

using namespace std;

int Task1(int n);
int Task2(int m, int a, int iter);

int main(){
	int n, m, iter = 0;
	bool flag = true;
	while (flag){
		iter++;
		cout << "Введите первое случайное число: ";
		cin >> n;
		cout << "Введите второе случайное число: ";
		cin >> m;
		int a = Task1(n);
		int sum = Task2(m, a, iter);
		if (sum / m == 0){
			cout << "Выполнено за " << iter << " итерацию";
			flag = false;
		}
		else{
			cout << "Не получилось :(" << endl;
		}
	}
	return 0;
}

int Task1(int n){
	srand(time(0));
	const int A = 0, B = 10;
	int temp = 0;
	cout << "Поиск числа под условие:" << endl;
	while (temp <= n){
		temp += A + rand() % (B - A + 1);
		cout << temp << " ";
	}
	cout << endl << "Поиск закончен" << endl << "Итоговая сумма " << temp << endl;
	return temp;
}

int Task2(int m, int a, int iter){
	int temp = a, sum = 0;
	while (temp > 0){
		temp %= 10;
		sum += temp;
		temp /= 10;
	}
	return sum;
}
