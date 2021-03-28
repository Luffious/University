#include <iostream>
#include <iomanip>

using namespace std;

void firstTask() {

    // Инициализируем все начальные данные
    int u0 = 2; 
    int* x_boundaries = new int[2];
    x_boundaries[0] = 0; 
    x_boundaries[1] = 1;
    int *t_boundaries = new int[2]; 
    t_boundaries[0] = 0;
    t_boundaries[1] = 1;
    double h = 0.1;
    double delta_t = 0.1;
    double alpha1 = 0;
    double beta1 = 2;
    double aj = (-2 * delta_t) / pow(h, 2);
    double bj = 1 + ((4 * delta_t) / pow(h, 2));
    double cj = aj;

    // Находим границу N и M для j и n соответственно, чтобы по этим границам построить массив u

    int N = (((double)x_boundaries[1] - x_boundaries[0]) / h) + 1; 
    int M = ((double)t_boundaries[1] - t_boundaries[0]) / delta_t;
    double* alpha = new double[N - 1];
    double* beta = new double[N - 1];
    for (int i = 1; i < N - 1; i++) {
        alpha[i] = 0;
        beta[i] = 0;
    }
    alpha[0] = alpha1;
    beta[0] = beta1;
    double** u = new double* [M];
    for (int n = 0; n < M; n++) {
        u[n] = new double [N];
    }
    for (int n = M - 1; n >= 0; n--) {
        for (int j = 0; j < N; j++) {
            u[n][j] = 0;
        }
    }

    // Переносим данные из начальных и граничных условий в массив M - строка, N - столбец

    for (int n = M - 1; n >= 0; n--) {
        for (int j = 0; j < N; j++) {
            if (n == 0) {
                u[n][j] = 2;
            }
            if ((n != 0) and (j == 0)) {
                u[n][j] = 2;
            }
            if ((n != 0) and (j == N - 1)) {
                u[n][j] = 2 + (n * delta_t);
            }
        }
    }

    // Алгоритм

    for (int n = 0; n < M - 1; n++) {
        for (int j = 1; j < N - 1; j++) {
            alpha[j] = (-1 * aj) / (bj + cj * alpha[j - 1]);
            beta[j] = ((u[n][j] + pow(((((double) j) - 1) * h), 2) * delta_t - (4 * (double) n * pow(delta_t, 2))) - cj * beta[j - 1]) / (bj + cj * alpha[j - 1]);
        }
        for (int j = N - 2; j >= 0; j--) { 
            u[n + 1][j] = alpha[j] * u[n + 1][j + 1] + beta[j];
        }
    }

    // Вывод массива
    string roof(96, '--');
    cout << "Первое задание (неявная разностная схема):" << endl << roof << endl;
    for (int n = M - 1; n >= 0; n--) {
        cout << "|  " << n << "  || ";
        for (int j = 0; j < N; j++) {
            cout << fixed << setprecision(3) << u[n][j] << " | ";
        }
        cout << endl << roof << endl;
    }
    cout << "| n/j ||   ";
    for (int j = 0; j < N; j++) {
        if (j != N - 1) {
            cout << j << "   |   ";
        }
        else {
            cout << j << "  |";
        }
    }
    cout << endl << roof << endl;

    // Удаление динамических массивов

    delete []x_boundaries;
    delete []t_boundaries;
    delete []alpha;
    delete []beta;
    for (int n = 0; n < M; n++) {
       delete []u[n];
    }
}

void secondTask() {

    // Инициализируем все начальные данные

    int u0 = 4;
    int* x_boundaries = new int[2];
    x_boundaries[0] = 0;
    x_boundaries[1] = 1;
    int* t_boundaries = new int[2];
    t_boundaries[0] = 0;
    t_boundaries[1] = 1;
    double h = pow(10, -1);
    double delta_t = 0.005; // Подсчитанно аналитически, взято самое большое значение 

    // Находим границу N и M для j и n соответственно, чтобы по этим границам построить массив u

    int N = (((double)x_boundaries[1] - x_boundaries[0]) / h) + 1;
    int M = ((double)t_boundaries[1] - t_boundaries[0]) / delta_t;
    double** u = new double* [M];
    for (int n = 0; n < M; n++) {
        u[n] = new double[N];
    }
    for (int n = M - 1; n >= 0; n--) {
        for (int j = 0; j < N; j++) {
            u[n][j] = 0;
        }
    }

    // Переносим данные из начальных и граничных условий в массив M - строка, N - столбец

    for (int n = M - 1; n >= 0; n--) {
        for (int j = 0; j < N; j++) {
            if (n == 0) {
                u[n][j] = 4;
            }
            if ((n != 0) and (j == 0)) {
                u[n][j] = 4;
            }
            if ((n != 0) and (j == N - 1)) {
                u[n][j] = 4 + (n * delta_t);
            }
        }
    }

    // Алгоритм
    
    for (int n = 0; n < M - 1; n++) {
        for (int j = 1; j < N - 1; j++) {
            u[n + 1][j] = u[n][j] + (delta_t / pow(h, 2)) * (u[n][j + 1] - 2 * u[n][j] + u[n][j - 1]) + ((double) j - 1) * h * delta_t;
        }
    }
    
    // Вывод массива

    string roof(98, '--');
    cout << "Второе задание (явная разностная схема):" << endl << roof << endl;
    for (int n = M - 1; n >= 0; n--) {
        if (n < 10) {
            cout << "|   " << n << "   || ";
        }
        else if ((n >= 10) and (n < 100)) {
            cout << "|   " << n << "  || ";
        }
        else {
            cout << "|  " << n << "  || ";
        }
        for (int j = 0; j < N; j++) {
            cout << fixed << setprecision(3) << u[n][j] << " | ";
        }
        cout << endl << roof << endl;
    }
    cout << "|  n/j  ||   ";
    for (int j = 0; j < N; j++) {
        if (j != N - 1) {
            cout << j << "   |   ";
        }
        else {
            cout << j << "  |";
        }
    }
    cout << endl << roof << endl;

    // Удаление динамических массивов

    delete[]x_boundaries;
    delete[]t_boundaries;
    for (int n = 0; n < M; n++) {
        delete[]u[n];
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    firstTask();
    cout << endl << endl;
    secondTask();
}
