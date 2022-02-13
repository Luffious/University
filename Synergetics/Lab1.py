# импорт библиотек:
# sympy для переменных в уравнениях
from sympy import * 
# numpy для создания векторов(массивов)
import numpy as np 
# matplotlib.pyplot для создания и вывода графиков
import matplotlib.pyplot as plt 
# random для создания псевдослучайных чисел
import random 

# инициализируем начальные переменные x0, k1, k2, tau, delta_t, а так же количество точек и количество графиков
x0, k1, k2, tau, d_t, N, amount = 24, 1, 16/35, 7, 0.001, 5000, 10 
# инициализируем переменные x, y, lambda для уравнений
var('x, y, lmb')
# создаём вектор t для построения графиков, инициализируем его пустым, затем задаём ему значения от 0 до N шагом delta_t
t = np.zeros(N)
for i in range(1, N):
    t[i] = t[i - 1] + d_t

# инициализируем функции dx/dt и dy/dt для дальнейшего нахождения по ним координат стационарной точки
dx_dt = ((x0 - x) / tau) - k1 * x
dy_dt = ((-1 * y) / tau) + k1 * x - k2 * y
xy = linsolve((dx_dt, dy_dt), (x, y))
# вытаскиваем координаты стационарной точки в переменные xf и yf
(xf, yf) = next(iter(xy))

# находим коэффициенты матрицы A, после чего рассчитываем определитель матрицы A - lambda * E
a11 = diff(dx_dt, x)
a12 = diff(dx_dt, y)
a21 = diff(dy_dt, x)
a22 = diff(dy_dt, y)
solveset((a11 - lmb) * (a22 - lmb) - (a21 * a12), lmb)

# инициализируем пустые вектора для x и y
x = np.zeros(N)
y = np.zeros(N)

# инициализируем названия 3 графиков и их осей: Фазовый портрет системы, Динамика системы во времени x(t), Динамика системы во времени y(t)
f, phases = plt.subplots()
plt.get_current_fig_manager().canvas.manager.set_window_title('Фазовый портрет системы')
phases.set_title('Фазовый портрет системы')
phases.set_xlabel('x')
phases.set_ylabel('y')

f1, xdyn = plt.subplots()
plt.get_current_fig_manager().canvas.manager.set_window_title('Динамика системы во времени x(t)')
xdyn.set_title('Динамика системы во времени x(t)')
xdyn.set_xlabel('x')
xdyn.set_ylabel('t')

f2, ydyn = plt.subplots()
plt.get_current_fig_manager().canvas.manager.set_window_title('Динамика системы во времени y(t)')
ydyn.set_title('Динамика системы во времени y(t)')
ydyn.set_xlabel('y')
ydyn.set_ylabel('t')

for j in range(0, amount):
    # задаём начальный x и y случайными значениями (+- 5 от координат стационарной точки)
    x[0], y[0] = random.uniform(xf - 5, xf + 5), random.uniform(yf - 5, yf + 5)
    for i in range(1, N):
        # расчитываем x и y 
        x[i] = d_t * (((1 / tau) * (x0 - x[i - 1])) - k1 * x[i - 1]) + x[i - 1]
        y[i] = d_t * (((-1 / tau) * y[i - 1]) + k1 * x[i - 1] - k2 * y[i - 1]) + y[i - 1]
    # добавляем траектории, зависимости x(t) и y(t) в свои графики
    phases.plot(x, y, color='red')
    xdyn.plot(x, t, color='blue')
    ydyn.plot(y, t, color='green')

# выводим все графики
plt.show()