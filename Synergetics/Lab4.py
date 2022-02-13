# импорт библиотек:
# sympy для переменных в уравнениях
from sympy import * 
# numpy для создания векторов(массивов)
import numpy as np 
# matplotlib.pyplot для создания и вывода графиков
import matplotlib.pyplot as plt 
# random для создания псевдослучайных чисел
import random 

# инициализируем начальные переменные k, b, q, n1, n2, d, delta_t, а так же количество точек и количество графиков
k, b, q, n1, n2, d, d_t, N, amount = 7 / 36, 5 / 4, 2 / 3, 4 / 5, 34 / 35, 12 / 7, 0.003, 5000, 10 
# инициализируем переменные u0, u1, lambda для уравнений
var('u0, u1, lmb')
# создаём вектор t для построения графиков, инициализируем его пустым, затем задаём ему значения от 0 до N шагом delta_t
t = np.zeros(N)
for i in range(1, N):
    t[i] = t[i - 1] + d_t

# инициализируем функции du0/dt и du1/dt для дальнейшего нахождения по ним координат стационарной точки
du0_dt = k * u1 - b + q
du1_dt = u0 * (n1 - n2) + d
u0u1 = linsolve((du0_dt, du1_dt), (u0, u1))
# вытаскиваем координаты стационарной точки в переменные u0f и u1f
(u0f, u1f) = next(iter(u0u1))

# находим коэффициенты матрицы A, после чего рассчитываем определитель матрицы A - lambda * E
a11 = diff(du0_dt, u0)
a12 = diff(du0_dt, u1)
a21 = diff(du1_dt, u0)
a22 = diff(du1_dt, u1)
solveset((a11 - lmb) * (a22 - lmb) - (a21 * a12), lmb)

# инициализируем пустые вектора для u0 и u1
u0 = np.zeros(N)
u1 = np.zeros(N)

# инициализируем названия 3 графиков и их осей: Фазовый портрет системы, Динамика системы во времени u0(t), Динамика системы во времени u1(t)
f, phases = plt.subplots()
plt.get_current_fig_manager().canvas.manager.set_window_title('Фазовый портрет системы')
phases.set_title('Фазовый портрет системы')
phases.set_xlabel('u0')
phases.set_ylabel('u1')

f1, u0dyn = plt.subplots()
plt.get_current_fig_manager().canvas.manager.set_window_title('Динамика системы во времени u0(t)')
u0dyn.set_title('Динамика системы во времени u0(t)')
u0dyn.set_xlabel('u0')
u0dyn.set_ylabel('t')

f2, u1dyn = plt.subplots()
plt.get_current_fig_manager().canvas.manager.set_window_title('Динамика системы во времени u1(t)')
u1dyn.set_title('Динамика системы во времени u1(t)')
u1dyn.set_xlabel('u1')
u1dyn.set_ylabel('t')

for j in range(0, amount):
    # задаём начальный u0 и u1 случайными значениями (+- 5 от координат стационарной точки)
    u0[0], u1[0] = random.uniform(u0f - 5, u0f + 5), random.uniform(u1f - 5, u1f + 5)
    for i in range(1, N):
        # расчитываем u0 и u1 
        u0[i] = d_t * (k * u1[i - 1] - b + q) + u0[i - 1]
        u1[i] = d_t * ((u0[i - 1] * (n1 - n2)) + d) + u1[i - 1]
    # добавляем траектории, зависимости u0(t) и u1(t) в свои графики
    phases.plot(u0, u1, color='red')
    u0dyn.plot(u0, t, color='blue')
    u1dyn.plot(u1, t, color='green')

# выводим все графики
plt.show()