# импорт библиотек:
# sympy для переменных в уравнениях
from sympy import * 
# numpy для создания векторов(массивов)
import numpy as np 
# matplotlib.pyplot для создания и вывода графиков
import matplotlib.pyplot as plt 
# random для создания псевдослучайных чисел
import random 

# инициализируем delta_t, а так же количество точек и количество графиков
d_t, N, amount = 0.0003, 5000, 10 
# инициализируем переменные x1, x2, lambda для уравнений
var('x1, x2, lmb')
# создаём вектор t для построения графиков, инициализируем его пустым, затем задаём ему значения от 0 до N шагом delta_t
t = np.zeros(N)
for i in range(1, N):
    t[i] = t[i - 1] + d_t

# инициализируем функции dx1/dt и dx2/dt для дальнейшего нахождения по ним координат стационарной точки
dx1_dt = -1 * x1 - 4 * x2 - 3
dx2_dt = (7 / 8) * x1 - x2 - (3 / 4)
x1x2 = linsolve((dx1_dt, dx2_dt), (x1, x2))
# вытаскиваем координаты стационарной точки в переменные x1f и x2f
(x1f, x2f) = next(iter(x1x2))

# находим коэффициенты матрицы A, после чего рассчитываем определитель матрицы A - lambda * E
a11 = diff(dx1_dt, x1)
a12 = diff(dx1_dt, x2)
a21 = diff(dx2_dt, x1)
a22 = diff(dx2_dt, x2)
solveset((a11 - lmb) * (a22 - lmb) - (a21 * a12), lmb)

# инициализируем пустые вектора для x1 и x2
x1 = np.zeros(N)
x2 = np.zeros(N)

# инициализируем названия 3 графиков и их осей: Фазовый портрет системы, Динамика системы во времени x1(t), Динамика системы во времени x2(t)
f, phases = plt.subplots()
plt.get_current_fig_manager().canvas.manager.set_window_title('Фазовый портрет системы')
phases.set_title('Фазовый портрет системы')
phases.set_xlabel('x1')
phases.set_ylabel('x2')

f1, x1dyn = plt.subplots()
plt.get_current_fig_manager().canvas.manager.set_window_title('Динамика системы во времени x1(t)')
x1dyn.set_title('Динамика системы во времени x1(t)')
x1dyn.set_xlabel('x1')
x1dyn.set_ylabel('t')

f2, x2dyn = plt.subplots()
plt.get_current_fig_manager().canvas.manager.set_window_title('Динамика системы во времени x2(t)')
x2dyn.set_title('Динамика системы во времени x2(t)')
x2dyn.set_xlabel('x2')
x2dyn.set_ylabel('t')

for j in range(0, amount):
    # задаём начальный x1 и x2 случайными значениями (+- 5 от координат стационарной точки)
    x1[0], x2[0] = random.uniform(x1f - 5, x1f + 5), random.uniform(x2f - 5, x2f + 5)
    for i in range(1, N):
        # расчитываем x1 и x2 
        x1[i] = (x1[i - 1] - 4 * d_t * x2[i - 1] - 3 * d_t) / (1 + d_t)
        x2[i] = (x2[i - 1] + d_t * (7 / 8) * x1[i - 1] - (3 / 4) * d_t) / (1 + d_t)
    # добавляем траектории, зависимости x1(t) и x2(t) в свои графики
    phases.plot(x1, x2, color='red')
    x1dyn.plot(x1, t, color='blue')
    x2dyn.plot(x2, t, color='green')

# выводим все графики
plt.show()