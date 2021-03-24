#include <iostream>
#include <ctime>

using namespace std;

void matrixMultiplication(int N, double** A, double* B, double* C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i] += A[i][j] * B[j];
        }
    }
}

void printArray(int N, double** A) {
    cout.precision(2);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << fixed << A[i][j] << "\t";
        }
        cout << endl;
    }
}

void printArray(int N, double* A) {
    cout.precision(2);
    for (int i = 0; i < N; i++) {
        cout << fixed << A[i] << "\t";
    }
    cout << endl;
}

int main()
{
    int i, j;
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    int N;
    cout << "Введите размерность массивов: ";
    cin >> N;
    double** A = new double* [N];
    for (i = 0; i < N; i++) {
        A[i] = new double[N];
    }
    double* B = new double[N];
    double* C = new double[N];
    for (i = 0; i < N; i++) {
        C[i] = 0;
        double amp = (double) rand() / RAND_MAX;
        B[i] = (rand() % 5) * amp;
        for (j = 0; j < N; j++) {
            A[i][j] = (rand() % 5) * amp;
        }
    }
    matrixMultiplication(N, A, B, C);
    cout << "Массив А:" << endl;
    printArray(N, A);
    cout << "\n\nМассив B:" << endl;
    printArray(N, B);
    cout << "\n\nМассив C:" << endl;
    printArray(N, C);
    for (int i = 0; i < N; i++)
        delete[] A[i];
    delete[] A;
    delete[] B;
    delete[] C;
}
