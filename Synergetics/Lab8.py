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
d_t, N, trj_am, alp_am = 0.04, 25, 100, 3 
# инициализируем параметры beta и gamma для метода Рунге-Кутта 2-го порядка
b21 = 1
y1, y2 = 0.5, 0.5
# инициализируем переменные x1, x2, lambda, alpha, r, phi для уравнений
var('x1, x2, lmb, alp, r, phi')
# создаём вектор t для построения графиков, инициализируем его пустым, затем задаём ему значения от 0 до N шагом delta_t
t = np.zeros(N)
for i in range(1, N):
    t[i] = t[i - 1] + d_t
# создаём вектор альф для построения графиков, инициализируем его пустым, затем задаём ему значения -1, -0.2, 5
alphas = np.zeros(alp_am)
alphas[0] = -1
alphas[1] = -0.2
alphas[2] = 5

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
dx1_dt = alp * x1 - x2 - 0.2 * x1 * (np.power(x1, 2) + np.power(x2, 2))
dx2_dt = x1 + alp * x2 - 0.2 * x1 * (np.power(x1, 2) + np.power(x2, 2))
x1x2 = solve((dx1_dt, dx2_dt), (x1, x2))
# вытаскиваем координаты стационарной точки в переменные x1f, x2f
(x1f, x2f) = x1x2[0]
# выводим координаты стационарных точек
print("Неподвижная точка:\nx1 =", x1f, "\nx2 =", x2f, end='\n\n')

# находим коэффициенты матрицы A, после чего рассчитываем определитель матрицы A - lambda * E
a11 = diff(dx1_dt, x1)
a12 = diff(dx1_dt, x2)
a21 = diff(dx2_dt, x1)
a22 = diff(dx2_dt, x2)
A = solve((a11 - lmb) * (a22 - lmb) - (a21 * a12), lmb)
# выводим лямбды неподвижной точки
print("Лямбды первой неподвижной точки:\n\u03BB1 =", A[0].subs(x1, x1f).subs(x2, x2f).subs(alp, "\u03B1"))
print("\u03BB2 =", A[1].subs(x1, x1f).subs(x2, x2f).subs(alp, "\u03B1", end='\n\n'))

# инициализируем пустые вектора для x1 и x2
x1 = np.zeros(N)
x2 = np.zeros(N)

# инициализируем название и оси графика Бифуркационной диаграммы
x_1, x_2 = plot(x1f, x2f, show=False)
f, bifdiag = plt.subplots()
bifdiag.set_title("Бифуркационная диаграмма")
bifdiag.set_xlabel("\u03B1")
bifdiag.set_ylabel("f(\u03B1)")
x, y = x_1.get_points()
bifdiag.plot(x, y, color='r')
x, y = x_2.get_points()
bifdiag.plot(x, y, color='r')
bifdiag.legend(["x1 и x2"])

# сохраняем график в формате .png и закрываем его для дальнейшего использования    
f.savefig('bifdiag.png')
plt.close(f)

# переходим в полярные координаты
# инициализируем функции dr/dt и dph/dt
dr_dt = r * (alp - 0.2 * (np.power(r, 2)))
dph_dt = 1
rs = solve(dr_dt, r, rational=True)

for i in range(2):
    # инициализируем название и оси Фазового портрета для r при двух различных альфах
    rarr = np.zeros(2)
    rarr[0] = 0
    rarr[1] = 30
    r_s, = plot(dr_dt.subs(alp, rarr[i]), show=False)
    f, rphase1 = plt.subplots()
    title = 'Фазовый портрет r при \u03B1 = ' + str(rarr[i])
    rphase1.set_title(title)
    rphase1.set_xlabel("r")
    rphase1.set_ylabel("f(r)")
    x, y = r_s.get_points()
    rphase1.plot(x, y, color='r')
    rphase1.legend([dr_dt.subs(alp, "\u03B1")])

    # сохраняем график в формате .png и закрываем его для дальнейшего использования 
    path = 'rphase' + str(i + 1) + '.png'
    f.savefig(path)
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
            diff = 4
        if k == 1:
            diff = 2
        if k == 2:
            diff = 0.04
        # задаём начальные x1 и x2 случайными значениями (+- diff от координат стационарной точки)
        x1[0] = random.uniform(x1f - diff, x1f + diff)
        x2[0] = random.uniform(x2f - diff, x2f + diff)
        for i in range(1, N):
            # расчитываем x1 и x2 методом Рунге-Кутта 2-го порядка
            k1f1 = alphas[k] * x1[i - 1] - x2[i - 1] - 0.2 * x1[i - 1] * (np.power(x1[i - 1], 2) + np.power(x2[i - 1], 2))
            k2f1 = alphas[k] * x1[i - 1] + b21 * d_t * k1f1 - x2[i - 1] + b21 * d_t * k1f1 - 0.2 * x1[i - 1] + b21 * d_t * k1f1\
                * (np.power(x1[i - 1] + b21 * d_t * k1f1, 2) + np.power(x2[i - 1] + b21 * d_t * k1f1, 2))
            k1f2 = x1[i - 1] + alphas[k] * x2[i - 1] - 0.2 * x1[i - 1] * (np.power(x1[i - 1], 2) + np.power(x2[i - 1], 2))
            k2f2 = x1[i - 1] + b21 * d_t * k1f2 + alphas[k] * x2[i - 1] + b21 * d_t * k1f2 - 0.2 * x1[i - 1] + b21 * d_t * k1f2\
                * (np.power(x1[i - 1] + b21 * d_t * k1f2, 2) + np.power(x2[i - 1] + b21 * d_t * k1f2, 2))
            x1[i] = x1[i - 1] + d_t * y1 * k1f1 + d_t * y2 * k2f1
            x2[i] = x2[i - 1] + d_t * y1 * k1f2 + d_t * y2 * k2f2
        # добавляем траектории в свои графики
        phases.plot(x1, x2, color='r')
        x1dyn.plot(t, x1, color='g')
        x2dyn.plot(t, x2, color='g')

    # добавляем стационарные точки, сохраняем графики в формате .png и закрываем их для дальнейшего использования 
    x1dyn.legend(["стационарная точка"]) 
    x2dyn.legend(["стационарная точка"]) 
    dot1, = phases.plot(x1f, x2f, color='k', marker='.')
    phases.legend([dot1], ["стационарная точка"])  

    f.savefig('alpha = ' + str(alphas[k]) + '/phases.png')
    plt.close(f)
    f1.savefig('alpha = ' + str(alphas[k]) + '/x1dyn.png')
    plt.close(f1)
    f2.savefig('alpha = ' + str(alphas[k]) + '/x2dyn.png')
    plt.close(f2)
