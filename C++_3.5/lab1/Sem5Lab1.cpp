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
		cout << "������� ������ ��������� �����: ";
		cin >> n;
		cout << "������� ������ ��������� �����: ";
		cin >> m;
		int a = Task1(n);
		int sum = Task2(m, a, iter);
		if (sum / m == 0){
			cout << "��������� �� " << iter << " ��������";
			flag = false;
		}
		else{
			cout << "�� ���������� :(" << endl;
		}
	}
	return 0;
}

int Task1(int n){
	srand(time(0));
	const int A = 0, B = 10;
	int temp = 0;
	cout << "����� ����� ��� �������:" << endl;
	while (temp <= n){
		temp += A + rand() % (B - A + 1);
		cout << temp << " ";
	}
	cout << endl << "����� ��������" << endl << "�������� ����� " << temp << endl;
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
