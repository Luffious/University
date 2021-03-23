#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define N 13

int main(){
	//переменные
	FILE * file;
	int i, j, k, l;
	double temp, temp1;
	double arr[N][2], x2[N][3], x4[N][5], x2T[3][N], x4T[5][N], x2Tx2[3][6] = {{0}}, x4Tx4[5][10] = {{0}};
	double x2Tx2obrT[3][N] = {{0}}, x4Tx4obrT[5][N] = {{0}}, a2[3] = {0}, a4[5] = {0}, y2[N], y4[N];
	double f3[4][4] = {{0}}, f5[6][6] = {{0}}, b3[4] = {0}, b5[6] = {0}, f3obr[4][8], f5obr[6][12], a3[4] = {0}, a5[6] = {0}, y3[N], y5[N];
	//считывание входных данных с файла
	if ((file = fopen("input.txt", "r")) == 0){
		puts("File does not exist");
		exit(1);
	}
	for (i = 0; i < N; i++){
		for (j = 0; j < 2; j++){
			fscanf(file, "%lf", &arr[i][j]);
		}
	}
	fclose(file);
	//создание матриц X для полиномов 2-й и 4-й степени
	for (i = 0; i < N; i++){
		x2[i][0] = 1;
		x4[i][0] = 1;
		for (j = 1; j < 3; j++){
			x2[i][j] = pow(arr[i][0], j);
		}
		for (j = 1; j < 5; j++){
			x4[i][j] = pow(arr[i][0], j);
		}
	}
	//создание транспонированных матриц X для полиномов 2-й и 4-й степени
	for (i = 0; i < 3; i++){
		for (j = 0; j < N; j++){
			temp = x2T[i][j];
			x2T[i][j] = x2[j][i];
			x2[j][i] = temp;
		}
	}
	for (i = 0; i < 5; i++){
		for (j = 0; j < N; j++){
			temp = x4T[i][j];
			x4T[i][j] = x4[j][i];
			x4[j][i] = temp;
		}
	}
	for (i = 0; i < N; i++){
		x2[i][0] = 1;
		x4[i][0] = 1;
		for (j = 1; j < 3; j++){
			x2[i][j] = pow(arr[i][0], j);
		}
		for (j = 1; j < 5; j++){
			x4[i][j] = pow(arr[i][0], j);
		}
	}
	//перемножение матриц X на их транспонированные версии для полиномов 2-й и 4-й степени
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			for (k = 0; k < N; k++){
				x2Tx2[i][j] += x2T[i][k] * x2[k][j];
			}
		}
	}
	x2Tx2[0][0]++;
	for (i = 0; i < 5; i++){
		for (j = 0; j < 5; j++){
			for (k = 0; k < N; k++){
				x4Tx4[i][j] += x4T[i][k] * x4[k][j];
			}
		}
	}
	x4Tx4[0][0]++;
	//обращение произведения матриц для полиномов 2-й и 4-й степени
	for (i = 0; i < 3; i++){
		for (j = 3; j < 6; j++){
			if (i + 3 == j){
				x2Tx2[i][j] = 1;
			}
			else{
				x2Tx2[i][j] = 0;
			}
		}
	}
	for (i = 0; i < 5; i++){
		for (j = 5; j < 10; j++){
			if (i + 5 == j){
				x4Tx4[i][j] = 1;
			}
			else{
				x4Tx4[i][j] = 0;
			}
		}
	}
	for (i = 0; i < 3; i++){
		temp = x2Tx2[i][i];
		for (j = 0; j < 6; j++){
			x2Tx2[i][j] /= temp;
		}
		for (k = 0; k < 3; k++){
			if (k != i){
				temp1 = x2Tx2[k][i];
				for (j = 0; j < 6; j++){
					x2Tx2[k][j] -= x2Tx2[i][j] * temp1;
				}
			}
		}
	}
	for (i = 0; i < 5; i++){
		temp = x4Tx4[i][i];
		for (j = 0; j < 10; j++){
			x4Tx4[i][j] /= temp;
		}
		for (k = 0; k < 5; k++){
			if (k != i){
				temp1 = x4Tx4[k][i];
				for (j = 0; j < 10; j++){
					x4Tx4[k][j] -= x4Tx4[i][j] * temp1;
				}
			}
		}
	}
	//умножение предыдущих результатов на транспонированную матрицу X для полиномов 2-й и 4-й степени
	for (i = 0; i < 3; i++){
		for (j = 0; j < N; j++){
			for (k = 3, l = 0; k < 6; k++, l++){
				x2Tx2obrT[i][j] += x2Tx2[i][k] * x2T[l][j];
			}
		}
	}
	for (i = 0; i < 5; i++){
		for (j = 0; j < N; j++){
			for (k = 5, l = 0; k < 10; k++, l++){
				x4Tx4obrT[i][j] += x4Tx4[i][k] * x4T[l][j];
			}
		}
	}
	//домножение предыдущих результатов на вектор y для полиномов 2-й и 4-й степени
	for (i = 0; i < 3; i++){
		for (j = 0; j < N; j++){
			a2[i] += x2Tx2obrT[i][j] * arr[j][1];
		}
	}
	for (i = 0; i < 5; i++){
		for (j = 0; j < N; j++){
			a4[i] += x4Tx4obrT[i][j] * arr[j][1];
		}
	}
	//создание матриц F для полиномов 3-й и 5-й степени
	for (i = 0; i < 4; i++){
		l = i;
		for (j = 0; j < 4; j++, l++){
			for (k = 0; k < N; k++){
				f3[i][j] += pow(arr[k][0], l);
			}
		}
	}
	f3[0][0] = N + 1;
	for (i = 0; i < 6; i++){
		l = i;
		for (j = 0; j < 6; j++, l++){
			for (k = 0; k < N; k++){
				f5[i][j] += pow(arr[k][0], l);
			}
		}
	}
	f5[0][0] = N + 1;
	//создание вектора b для полиномов 3-й и 5-й степени
	for (i = 0; i < 4; i++){
		for (j = 0; j < N; j++){
			b3[i] += pow(arr[j][0], i) * arr[j][1];
		}
	}
	for (i = 0; i < 6; i++){
		for (j = 0; j < N; j++){
			b5[i] += pow(arr[j][0], i) * arr[j][1];
		}
	}
	//обращаем матрицы F для полиномов 3-й и 5-й степени
	for (i = 0; i < 4; i++){
		for (j = 0; j < 8; j++){
			if (i + 4 == j){
				f3obr[i][j] = 1;
			}
			else if (j < 4){
				f3obr[i][j] = f3[i][j];
			}
			else{
				f3obr[i][j] = 0;
			}
		}
	}
	for (i = 0; i < 6; i++){
		for (j = 0; j < 12; j++){
			if (i + 6 == j){
				f5obr[i][j] = 1;
			}
			else if (j < 6){
				f5obr[i][j] = f5[i][j];
			}
			else{
				f5obr[i][j] = 0;
			}
		}
	}
	for (i = 0; i < 4; i++){
		temp = f3obr[i][i];
		for (j = 0; j < 8; j++){
			f3obr[i][j] /= temp;
		}
		for (k = 0; k < 4; k++){
			if (k != i){
				temp1 = f3obr[k][i];
				for (j = 0; j < 8; j++){
					f3obr[k][j] -= f3obr[i][j] * temp1;
				}
			}
		}
	}
	for (i = 0; i < 6; i++){
		temp = f5obr[i][i];
		for (j = 0; j < 12; j++){
			f5obr[i][j] /= temp;
		}
		for (k = 0; k < 6; k++){
			if (k != i){
				temp1 = f5obr[k][i];
				for (j = 0; j < 12; j++){
					f5obr[k][j] -= f5obr[i][j] * temp1;
				}
			}
		}
	}
	//перемножение обратных матриц F на вектор y для полиномов 3-й и 5-й степени
	for (i = 0; i < 4; i++){
		for (j = 4; j < 8; j++){
			a3[i] += f3obr[i][j] * b3[j - 4];
		}
	}
	for (i = 0; i < 6; i++){
		for (j = 6; j < 12; j++){
			a5[i] += f5obr[i][j] * b5[j - 6];
		}
	}
	//создание векторов y* для полиномов 2-й, 3-й, 4-й и 5-й степени
	for (i = 0; i < N; i++){
		y2[i] = a2[0] + a2[1] * arr[i][0] + a2[2] * pow(arr[i][0], 2);
		y3[i] = a3[0] + a3[1] * arr[i][0] + a3[2] * pow(arr[i][0], 2) + a3[3] * pow(arr[i][0], 3);
		y4[i] = a4[0] + a4[1] * arr[i][0] + a4[2] * pow(arr[i][0], 2) + a4[3] * pow(arr[i][0], 3) + a4[4] * pow(arr[i][0], 4);
		y5[i] = a5[0] + a5[1] * arr[i][0] + a5[2] * pow(arr[i][0], 2) + a5[3] * pow(arr[i][0], 3) + a5[4] * pow(arr[i][0], 4)
		+ a5[5] * pow(arr[i][0], 5);
	}
	//вывод векторов y* для полиномов 2-й, 3-й, 4-й и 5-й степени
	ofstream out;
	out.open("output.txt");
	cout.precision(7);
	cout << "y* для полинома:" << endl << "2-й\t\t" << "3-й\t\t" << "4-й\t\t" << "5-й\t\t" << endl;
	for (i = 0; i < N; i++){
		cout << fixed << y2[i] << "\t" << y3[i] << "\t" << y4[i] << "\t" << y5[i] << endl;
		out << fixed << y2[i] << "\t" << y3[i] << "\t" << y4[i] << "\t" << y5[i] << endl;
	}
	out.close();
}
