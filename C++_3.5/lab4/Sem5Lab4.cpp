#include <iostream>

using namespace std;

class Druid
{
public:
    int power = 0;
    int cost = 0;
    void action() {
        cout << "Список действий: двигаться, атаковать, произнести заклинание, пропустить ход" << endl;
    }
    void powerToCostRatio() {
        cout.precision(2);
        cout << "Отношения силы к стоимости: " << fixed << (double) power / cost << endl;
    }
    Druid(int power, int cost) {
        this->power = power;
        this->cost = cost;
    }
};

class Monk
{
public:
    int power = 0;
    int cost = 0;
    void action() {
        cout.precision(2);
        cout << "Список действий: двигаться, атаковать, регенерировать здоровье, пропустить ход" << endl;
    }
    void powerToCostRatio() {
        cout << "Отношения силы к стоимости: " << fixed << (double) power / cost << endl;
    }
    Monk(int power, int cost) {
        this->power = power;
        this->cost = cost;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Monk LiuKang(20, 700);
    Druid Tieru(40, 1000);
    LiuKang.action();
    LiuKang.powerToCostRatio();
    Tieru.action();
    Tieru.powerToCostRatio();
}

