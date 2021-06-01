#include <random>
#include <iostream>

#define PI 3.14

using namespace std;

double F(double x)
{
    return (pow(x, 2) + 10 - (10 * cos(2 * PI * x)));
}

double C(double val)
{
    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::cauchy_distribution<> distribution(0.0, 1.0);
   return distribution(gen);
}

double G(double x, double t)
{
    return (x + C(x));
}

double H(double dE, double t)
{
    return exp(-dE / t);
}

double GetRandAlpha()
{
    return static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
}

int main()
{
    srand(time(0));
	setlocale(LC_ALL, "ru");
    double x = -10; 
    double nX = x;
    double startT = 100;
    double T = startT;
    double endT = 0.1;
    double minGlobal = F(x);
    double h = 0.01;
    for (int k = 1; ; k++)
    {
        if (F(nX) < minGlobal)
            minGlobal = F(nX);
        T = startT / k;
        if (T <= endT)
            break;
        nX = G(x, T);
        while (true)
        {
            if (GetRandAlpha() < H(F(nX) - F(x), T))
            {
                x = nX;
                break;
            }
            else
                nX = G(x, T);
        }
    }
    cout << "x = " << x << endl;
    cout << "Глобальный минимум функции = " << F(x) << endl;
    return 0;
}