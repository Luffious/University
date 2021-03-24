#include <iostream>
#include <string>

using namespace std;

struct BankNote {
    string name;
    double faceValue;
    double exchangeRateToRub;
};

void sumOfArray(BankNote* A, int amount) {
    double sum = 0;
    for (int i = 0; i < amount; i++) {
        sum += A[i].exchangeRateToRub * A[i].faceValue;
    }
    cout.precision(2);
    cout << fixed << "Сумма массива структур: " << sum << endl;
}

void sumOfArray(int* A, int amount) {
    int sum = 0;
    for (int i = 0; i < amount; i++) {
        sum += A[i];
    }
    cout << "Сумма массива интов: " << sum << endl;
}

void convertationOfBankNote(BankNote* A, int amount) {
    double convertation = A[0].faceValue * A[0].exchangeRateToRub / A[1].exchangeRateToRub;
    cout << A[0].faceValue << " " << A[0].name << " = " << convertation << " " << A[1].name;
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int amount = 2;
    BankNote* BankNotes;
    BankNotes = new BankNote[amount];
    for (int i = 0; i < amount; i++) {
        cout << "Введите название валюты: ";
        cin >> BankNotes[i].name;
        cout << "Введите номинал этой валюты: ";
        cin >> BankNotes[i].faceValue;
        cout << "Введите курс этой валюты к рублю: ";
        cin >> BankNotes[i].exchangeRateToRub;
    }
    sumOfArray(BankNotes, amount);
    convertationOfBankNote(BankNotes, amount);
    delete[] BankNotes;
}
