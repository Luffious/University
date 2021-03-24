#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <cstdlib>

using namespace std;

void selectionSort(vector<double> x);

int main(void)
{
    setlocale(LC_ALL, "Russian");
    ofstream outf("Output.txt");
    if (!outf) {
        cerr << "ERROR!!" << endl;
        exit(1);
    }
    const int M = 20;
    const int N_amount = 8;
    int N = 1000;
    mt19937 engine(time(0));
    uniform_real_distribution<double> gen(-1.0, 1.0);
    for (int j = 0; j < N_amount; j++) {
        cout << endl << "Количество элементов: " << N << endl;
        outf << endl << "Количество элементов: " << N << endl;
        for (int i = 0; i < M; i++) {
            vector<double> v(N);
            for (auto& el : v)
                el = gen(engine);
            chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
            selectionSort(v);
            chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
            chrono::duration<double, nano> nano_diff = end - start;
            chrono::duration<double, micro> micro_diff = end - start;
            chrono::duration<double, milli> milli_diff = end - start;
            chrono::duration<double> sec_diff = end - start;
            outf << endl;
            outf << "Time: " << nano_diff.count() << " nano sec." << endl;
            outf << "Time: " << micro_diff.count() << " micro sec." << endl;
            outf << "Time: " << milli_diff.count() << " milli sec." << endl;
            outf << "Time: " << sec_diff.count() << " sec." << endl;
            v.clear();
        }
        N *= 2;
    }
}

void selectionSort(vector<double> x) {
    for (int i = 0; i < x.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < x.size(); j++) {
            if (x[j] < x[min]) {
                min = j;
            }
        }
        double temp = x[i];
        x[i] = x[min];
        x[min] = temp;
    }
}

 
