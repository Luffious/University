# 24 Вариант
# 24 Вариант
# 1 Пункт
a0, a1, a2, a3 = 1.01365, 1.21548e-2, 1.5447e-3, 6.42463e-5


def k_find(ww: float, tt: float):
    return a0 - a1 * ww - (a2 - a3 * ww) * tt


k_real = [[0] * 5 for i in range(5)]
out = open('output.txt', 'w')
print("Введите 1 для ввода данных вручную или 2 для ввода данных с файла:", end=' ')
c = input()
while c != '1' and c != '2':
    print("Ошибка. Введите корректное значение")
    c = input()
if c == '1':
    k_real = [[0] * 5 for i in range(5)]
    for i in range(5):
        for j in range(5):
            print("Введите дробное число -", j, "элемент", i, "строки в пределах от 0 до 1 не включая концы:")
            condition, condition1, condition2 = True, False, False
            temp = ''
            while condition or condition1 or condition2:
                temp = input()
                e = temp.split()
                e = ''.join(e)
                temp = e
                d = temp.find(',')
                condition1 = temp.isalpha()
                condition2 = temp.isalnum()
                try:
                    k_real[i][j] = int(temp)
                    print("ОШИБКА! Неверный формат")
                    condition = True
                except ValueError:
                    try:
                        k_real[i][j] = float(temp)
                        if k_real[i][j] > 1 or k_real[i][j] < 0:
                            print("ОШИБКА! Число вне диапазона")
                            condition = True
                        else:
                            condition = False
                    except ValueError:
                        if d == 1:
                            try:
                                temp = temp[0] + '.' + temp[2:]
                                k_real[i][j] = float(temp)
                                if k_real[i][j] > 1 or k_real[i][j] < 0:
                                    print("ОШИБКА! Число вне диапазона")
                                    condition = True
                                else:
                                    condition = False
                            except ValueError:
                                print("ОШИБКА! Неверный формат")
                                condition = True
                if condition1:
                    print("ОШИБКА! Неверный формат")
            k_real[i][j] = float(temp)
elif c == '2':
    k_real = [[0] * 5 for i in range(5)]
    try:
        with open('input.txt') as inp:
            lst = list()
            for line in inp.readlines():
                lst.extend(line.rstrip().split(' '))
                k = 0
    except IOError:
        print("Файл отсутствует")
        quit()
    for i in range(len(k_real)):
        for j in range(len(k_real[i])):
            k_real[i][j] = float(lst.pop(k))
inp.close()
w = [85.10, 89.10, 90.45, 91.42, 92.75]
t = [130.00, 140.12, 150.25, 160.92, 170.42]
out.write("Экспериментальные данные:\n")
print("Экспериментальные данные:")
for i in range(len(k_real)):
    for j in range(len(k_real[i])):
        if c == '2':
            if k_real[i][j] == 0:
                out.write('------\t')
                print('------', end='\t')
            else:
                out.write(str(k_real[i][j]))
                out.write('\t')
                print(k_real[i][j], end='\t')
        elif c == '1':
            if k_real[i][j] == 0:
                out.write(str(k_real[i][j]))
                out.write('   \t')
                print(k_real[i][j], '   ', end='\t')
            else:
                out.write(str(k_real[i][j]))
                out.write('\t')
                print(k_real[i][j], end='\t')
    out.write('\n')
    print()
out.write('\n')
print()
out.write("Рассчитаные данные:\n")
print("Рассчитаные данные:")
k_comp = [[0] * 5 for i in range(5)]
precis = [[float(0)] * 5 for i in range(5)]
for n in range(2):
    for i in range(len(k_comp)):
        for j in range(len(k_comp[i])):
            k_comp[i][j] = k_find(w[i], t[j])
            if i == 0 and j > 2:
                k_comp[i][j] = 0
            if i == 1 and j == 4:
                k_comp[i][j] = 0
            if n == 0:
                if k_comp[i][j] == 0:
                    out.write('------')
                    out.write('\t')
                    print('------', end='\t')
                else:
                    out.write(str(round(k_comp[i][j], 4)))
                    out.write('\t')
                    print(round(k_comp[i][j], 4), end='\t')
            else:
                precis[i][j] = round(abs(k_comp[i][j] - k_real[i][j]), 4)
                if k_comp[i][j] == 0:
                    out.write('------')
                    out.write('\t')
                    print('------', end='\t')
                else:
                    if precis[i][j] <= 0.00001:
                        out.write(str(precis[i][j]))
                        out.write('   \t')
                        print(precis[i][j], '   ', end='\t')
                    else:
                        out.write(str(precis[i][j]))
                        out.write('\t')
                        print(precis[i][j], end='\t')
        out.write('\n')
        print()
    out.write('\n')
    print()
    if n == 0:
        out.write('Дельта погрешности по 1 пункту\n')
        print("Дельта погрешности по 1 пункту:")
# 2 Пункт
out.write("Дельта погрешности по 2 пункту:\n")
print("Дельта погрешности по 2 пункту:")
for i in range(len(w)):
    w_temp = [w[i] for w_temp in w]
    k_map = list(map(lambda a, b: a0 - a1 * a - (a2 - a3 * a) * b, w_temp, t))
    for j in range(len(k_map)):
        if i == 0 and j > 2:
            k_map[j] = 0
        if i == 1 and j == 4:
            k_map[j] = 0
        precis[i][j] = round(abs(k_map[j] - k_real[i][j]), 4)
        if k_map[j] == 0:
            out.write('------')
            out.write('\t')
            print('------', end='\t')
        else:
            if precis[i][j] <= 0.00001:
                out.write(str(precis[i][j]))
                out.write('   \t')
                print(precis[i][j], '   ', end='\t')
            else:
                out.write(str(precis[i][j]))
                out.write('\t')
                print(precis[i][j], end='\t')
    out.write('\n')
    print()
