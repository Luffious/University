#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Hero
{
private:
    int _power;
    int _cost;
protected:
    Hero(int _power, int _cost, bool druid, bool monk) :
        _power(_power),
        _cost(_cost),
        druid(druid),
        monk(monk)
    {}
public:
    bool druid;
    bool monk;
    int getPower() {
        return _power;
    }
    int getCost() {
        return _cost;
    }
};

class Druid : public Hero
{
public:
    Druid(int power, int cost) :
        Hero( power, cost, true, false)
    {}
    void listOfActions() {
        cout << "Список действий: двигаться, атаковать, произнести заклинание, пропустить ход" << endl;
    }
    void castAction() {
        cout << "Друид произносит заклинание" << endl;
    }
};

class Monk : public Hero
{
public:
    Monk(int power, int cost) :
        Hero(power, cost, false, true)
    {}
    void listOfActions() {
        cout << "Список действий: двигаться, атаковать, регенерировать здоровье, пропустить ход" << endl;
    }
    void regenerationAction() {
        cout << "Монах производит лечение" << endl;
    }
};

class Tavern
{
private:
    int HEROES_AMOUNT = 0;
    int N = 0, K = 0;
    Hero** p_hero;
    void _recruitHeroes() {
        do {
            generateHeroes();
        } while (!_checkForRequirements());
    }
    bool _checkForRequirements() {
        int power_sum = 0, cost_sum = 0;
        for (int i = 0; i < HEROES_AMOUNT; i++) {
            power_sum += p_hero[i]->getPower();
            cost_sum += p_hero[i]->getCost();
        }
        if (power_sum <= N && cost_sum <= K) {
            cout << "Общая сила: " << power_sum << endl;
            cout << "Общая стоимость: " << cost_sum << endl;
            return true;
        }
        else {
            return false;
        }
    }
public:
    void generateHeroes() {
        int power_sum = 0, cost_sum = 0;
        for (int i = 0; i < HEROES_AMOUNT; i++) {
            int j = rand() % 2;
            if (j == 1) {
                cout << "\nПо воле случая класс вашего героя - Друид\n";
                p_hero[i] = new Druid(rand() % 100, rand() % 100);
            }
            else {
                cout << "\nПо воле случая класс вашего героя - Монах\n";
                p_hero[i] = new Monk(rand() % 100, rand() % 100);
            }
            cout << endl;
        }
    }
public:
    Tavern(int HEROES_AMOUNT, int N, int K)
    {
        this->HEROES_AMOUNT = HEROES_AMOUNT;
        this->N = N;
        this->K = K;
        p_hero = new Hero * [HEROES_AMOUNT];
        _recruitHeroes();
    }
};

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    int power_sum, cost_sum;
    cout << "Введите общую силу героев: ";
    cin >> power_sum;
    cout << "Введите цену героя: ";
    cin >> cost_sum;
    Tavern tavern(10, power_sum, cost_sum);
}

