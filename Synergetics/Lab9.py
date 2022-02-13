# импорт библиотек:
# sympy для переменных в уравнениях
from sympy import * 
# numpy для создания векторов(массивов)
import numpy as np 
# matplotlib.pyplot для создания и вывода графиков
import matplotlib.pyplot as plt 
# random для создания псевдослучайных чисел
import random 
# os для создания директорий, куда будут сохраняться графики
from os import *

# инициализируем delta_t, а так же x0, количество точек, количество траекторий
x0, d_t, N, trj_am = 0.6, 1, 30, 100
# инициализируем переменные x1, x2, lambda, alpha для уравнений
var('x, alp')
# создаём вектор t для построения графиков, инициализируем его пустым, затем задаём ему значения от 0 до N шагом delta_t
t = np.zeros(N)
for i in range(1, N):
    t[i] = t[i - 1] + d_t
# создаём вектор альф для построения графиков, инициализируем его с значениями из задания
alphas = np.array([0.95, 1.15, 1.67, 1.77, 1.825, 1.83, 1.85, 1.87, 1.874, 1.89, 1.95, 2.05, 2.11])
# инициализируем переменную с количеством альф
alp_am = alphas.size

# инициализируем функцию f(alp, x) для дальнейшего нахождения по ней координаты стационарных точек
func = alp * x * (1 - np.power(x, 3)) - x
x = solve(func, x)
# вытаскиваем координату стационарных точек в переменные x1f, x2f
x1f = x[0]
x2f = x[1]
# выводим координаты стационарных точек
print("Неподвижные точки:\nx1 =", x1f, "\nx2 =", x2f.subs(alp, "\u03B1"), end='\n\n')

# инициализируем пустой вектор для x
x = np.zeros(N)

# добавляем данную строку, чтобы не вылезали ошибки о NaN
np.seterr(all="ignore")

# инициализируем название и оси графика Бифуркационной диаграммы
x_1, x_2 = plot(x1f, x2f, show=False)
f, bifdiag = plt.subplots()
bifdiag.set_title("Бифуркационная диаграмма")
bifdiag.set_xlabel("\u03B1")
bifdiag.set_ylabel("f(\u03B1)")
x1, x2 = x_1.get_points()
bifdiag.plot(x1, x2, color='r')
x1, x2 = x_2.get_points()
bifdiag.plot(x1, x2, color='b')
bifdiag.plot(1, x2f.subs(alp, 1), color='k', marker='.')
bifdiag.legend(["x1", "x2", "точка бифуркации"])

# сохраняем график в формате .png и закрываем его для дальнейшего использования    
f.savefig('bifdiag.png')
plt.close(f)

# решаем
for k in range(alp_am):
    # инициализируем названия графика и его осей: Фазовый портрет системы
    f, phases = plt.subplots()
    phases.set_title('Фазовый портрет системы (\u03B1 = ' + str(alphas[k]) + ')')
    phases.set_xlabel('t')
    phases.set_ylabel('x')

    # задаём начальный x
    x[0] = x0
    for i in range(1, N):
        # расчитываем x
        x[i] = alphas[k] * x[i - 1] * (1 - np.power(x[i - 1], 3))
    # добавляем траекторию в график
    phases.plot(t, x, color='r')
    # сохраняем график в формате .png и закрываем его для дальнейшего использования 
    f.savefig('phases' + str(k) + '.png')
    plt.close(f)