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

# инициализируем delta_t, а так же количество точек, количество траекторий и количество альф
d_t, N, trj_am, alp_am = 0.04, 15, 100, 3 
# инициализируем переменные x1, x2, lambda, alpha для уравнений
var('x1, x2, lmb, alp')
# создаём вектор t для построения графиков, инициализируем его пустым, затем задаём ему значения от 0 до N шагом delta_t
t = np.zeros(N)
for i in range(1, N):
    t[i] = t[i - 1] + d_t
# создаём вектор альф для построения графиков, инициализируем его пустым, затем задаём ему значения от -0.6 до 0.6 шагом 0.6
alphas = np.zeros(N)
alphas = np.arange(-0.6, 0.61, 0.6)

# создаём директории для графиков
print("Создаём директории:")
for i in range(alp_am):
    try:
        mkdir('alpha = ' + str(alphas[i]))
        print("Директория alpha = " + str(alphas[i]) + " создана")
    except FileExistsError:
        print("Директория alpha = " + str(alphas[i]) + " уже существуют")
print(end='\n\n')

# инициализируем функции dx1/dt и dx2/dt для дальнейшего нахождения по ним координат стационарных точек
dx1_dt = 5 * np.power(x1, 2) + 3 * alp
dx2_dt = -1 * x1 - x2 - (3 * alp / 2)
x1x2 = solve((dx1_dt, dx2_dt), (x1, x2))
# вытаскиваем координаты стационарных точек в переменные x1f1, x2f1 и x1f2, x2f2
(x1f1, x2f1) = x1x2[0]
(x1f2, x2f2) = x1x2[1]
# выводим координаты стационарных точек
print("Первая неподвижная точка:\nx1 =", x1f1.subs(alp, "\u03B1"), "\nx2 =", x2f1.subs(alp, "\u03B1"), end='\n\n')
print("Вторая неподвижная точка:\nx1 =", x1f2.subs(alp, "\u03B1"), "\nx2 =", x2f2.subs(alp, "\u03B1"), end='\n\n\n')

# находим коэффициенты матрицы A, после чего рассчитываем определитель матрицы A - lambda * E
a11 = diff(dx1_dt, x1)
a12 = diff(dx1_dt, x2)
a21 = diff(dx2_dt, x1)
a22 = diff(dx2_dt, x2)
A = solve((a11 - lmb) * (a22 - lmb) - (a21 * a12), lmb)
# выводим лямбды для обеих неподвижных точек
print("Лямбды первой неподвижной точки:\n\u03BB1 =", A[0], "\n\u03BB2 =", A[1].subs(x1, x1f1).subs(alp, "\u03B1"), end='\n\n')
print("Лямбды второй неподвижной точки:\n\u03BB1 =", A[0], "\n\u03BB2 =", A[1].subs(x1, x1f2).subs(alp, "\u03B1"))

# инициализируем пустые вектора для x1_f1, x2_f1 и x1_f2, x2_f2
x1_f1 = np.zeros(N)
x2_f1 = np.zeros(N)
x1_f2 = np.zeros(N)
x2_f2 = np.zeros(N)

# инициализируем название и оси графика Бифуркационной диаграммы
x1_1, x2_1, x1_2, x2_2 = plot(x1f1, x2f1, x1f2, x2f2, show=False)
f, bifdiag = plt.subplots()
plt.get_current_fig_manager().canvas.manager.set_window_title("Бифуркационная диаграмма")
bifdiag.set_title("Бифуркационная диаграмма")
bifdiag.set_xlabel("\u03B1")
bifdiag.set_ylabel("f(\u03B1)")
x, y = x1_1.get_points()
bifdiag.plot(x, y, color='r')
x, y = x2_1.get_points()
bifdiag.plot(x, y, color='b')
x, y = x1_2.get_points()
bifdiag.plot(x, y, color='r')
x, y = x2_2.get_points()
bifdiag.plot(x, y, color='b')
bifdiag.legend(["x1", "x2"])

# сохраняем график в формате .png и закрываем его для дальнейшего использования    
f.savefig('bifdiag.png')
plt.close(f)

# решаем
for k in range(alp_am):
    # инициализируем названия 3 графиков и их осей: Фазовый портрет системы, Динамика системы во времени x1(t), Динамика системы во времени x2(t)
    f, phases = plt.subplots()
    phases.set_title('Фазовый портрет системы (\u03B1 = ' + str(alphas[k]) + ')')
    phases.set_xlabel('x1')
    phases.set_ylabel('x2')
    
    f1, x1dyn = plt.subplots()
    x1dyn.set_title('Динамика системы во времени x1(t) (\u03B1 = ' + str(alphas[k]) + ')')
    x1dyn.set_xlabel('t')
    x1dyn.set_ylabel('x1')

    f2, x2dyn = plt.subplots()
    x2dyn.set_title('Динамика системы во времени x2(t) (\u03B1 = ' + str(alphas[k]) + ')')
    x2dyn.set_xlabel('t')
    x2dyn.set_ylabel('x2')

    for j in range(trj_am):
        # задаём diffы для создания случайных начальных координат
        if k == 0:
            diff = 0.3
        if k == 1:
            diff = 0.2
        if k == 2:
            diff = 0.1
        # задаём начальные x1 и x2 случайными значениями (+- diff от координат стационарной точки)
        # для положительной альфы работаем с реальной частью комплексного числа
        if (k == 2):
            x1_f1_с = x1f1.subs(alp, alphas[k])
            x1_f1[0] = random.uniform(re(x1_f1_с) - diff, re(x1_f1_с) + diff)
            x2_f1_с = x2f1.subs(alp, alphas[k])
            x2_f1[0] = random.uniform(re(x2_f1_с) - diff, re(x2_f1_с) + diff)
            x1_f2_с = x1f2.subs(alp, alphas[k])
            x1_f2[0] = random.uniform(re(x1_f2_с) - diff, re(x1_f2_с) + diff)
            x2_f2_с = x2f2.subs(alp, alphas[k])
            x2_f2[0] = random.uniform(re(x2_f2_с) - diff, re(x2_f2_с) + diff)
        else:
            x1_f1[0] = random.uniform(x1f1.subs(alp, alphas[k]) - diff, x1f1.subs(alp, alphas[k]) + diff)
            x2_f1[0] = random.uniform(x2f1.subs(alp, alphas[k]) - diff, x2f1.subs(alp, alphas[k]) + diff)
            x1_f2[0] = random.uniform(x2f2.subs(alp, alphas[k]) - diff, x2f2.subs(alp, alphas[k]) + diff)
            x2_f2[0] = random.uniform(x1f2.subs(alp, alphas[k]) - diff, x1f2.subs(alp, alphas[k]) + diff)
        for i in range(1, N):
            # расчитываем x1 и x2 для обеих ситуаций
            x1_f1[i] = d_t * (5 * np.power(x1_f1[i - 1], 2) + 3 * alphas[k]) + x1_f1[i - 1]
            x2_f1[i] = d_t * (-1 * x1_f1[i - 1] - x2_f1[i - 1] - (3 * alphas[k] / 2)) + x2_f1[i - 1]
            x1_f2[i] = d_t * (5 * np.power(x1_f2[i - 1], 2) + 3 * alphas[k]) + x1_f2[i - 1]
            x2_f2[i] = d_t * (-1 * x1_f2[i - 1] - x2_f2[i - 1] - (3 * alphas[k] / 2)) + x2_f2[i - 1]
        # добавляем траектории в свои графики
        phases.plot(x1_f1, x2_f1, color='r')
        x1dyn.plot(t, x1_f1, color='g')
        x2dyn.plot(t, x2_f1, color='g')
        if (k == 0):
            phases.plot(x1_f2, x2_f2, color='b')
            x1dyn.plot(t, x1_f2, color='y')
            x2dyn.plot(t, x2_f2, color='y')

    # добавляем стационарные точки, сохраняем графики в формате .png и закрываем их для дальнейшего использования 
    if (k == 0): 
        x1dyn.legend(["1 стационарная точка", "2 стационарная точка"]) 
        x2dyn.legend(["1 стационарная точка", "2 стационарная точка"]) 
        dot1, = phases.plot(x1f1.subs(alp, alphas[k]), x2f1.subs(alp, alphas[k]), color='k', marker='.')
        dot2, = phases.plot(x1f2.subs(alp, alphas[k]), x2f2.subs(alp, alphas[k]), color='0.4', marker='.')
        phases.legend([dot1, dot2], ["1 стационарная точка", "2 стационарная точка"])  
    else:  
        x1dyn.legend(["стационарная точка"]) 
        x2dyn.legend(["стационарная точка"]) 
        if (k == 1): 
            dot1, = phases.plot(x1f1.subs(alp, alphas[k]), x2f1.subs(alp, alphas[k]), color='k', marker='.')
            phases.legend([dot1], ["стационарная точка"]) 
        else:
            dot1, = phases.plot(re(x1_f1_с), re(x2_f1_с), color='k', marker='.')
            phases.legend([dot1], ["стационарная точка"]) 
    f.savefig('alpha = ' + str(alphas[k]) + '/phases.png')
    plt.close(f)
    f1.savefig('alpha = ' + str(alphas[k]) + '/x1dyn.png')
    plt.close(f1)
    f2.savefig('alpha = ' + str(alphas[k]) + '/x2dyn.png')
    plt.close(f2)