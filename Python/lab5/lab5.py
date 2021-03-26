# 24 Вариант
# 1 Пункт
a0, a1, a2, a3 = 1.01365, 1.21548 * pow(10, -2), 1.5447 * pow(10, -3), 6.42463 * pow(10, -5)


def k(a, b):
    x = a0 - a1 * a - (a2 - a3 * a) * b
    return x


w = [85.10, 89.10, 90.45, 91.42, 92.75]
t = [130.00, 140.12, 150.25, 160.92, 170.42]
k_real = [[0.4904, 0.5299, 0.5685, 0, 0],
          [0.4747, 0.5169, 0.5589, 0.6033, 0],
          [0.4702, 0.5133, 0.5568, 0.6020, 0.6411],
          [0.4665, 0.5098, 0.5536, 0.5996, 0.6397],
          [0.4606, 0.5055, 0.5495, 0.5960, 0.6384]]
for i in range(len(w)):
    for j in range(len(t)):
        k_comp = k(w[i], t[j])
        if i == 0 and j > 2:
            k_comp = 0
        if i == 1 and j == 4:
            k_comp = 0
        precis = round(abs(k_comp - k_real[i][j]), 4)
        print(precis, end=' ')
    print()
print()
# 2 Пункт
for i in range(len(w)):
    w_temp = [w[i] for w_temp in w]
    k_map = list(map(lambda a, b: a0 - a1 * a - (a2 - a3 * a) * b, w_temp, t))
    for j in range(len(t)):
        if i == 0 and j > 2:
            k_map[j] = 0
        if i == 1 and j == 4:
            k_map[j] = 0
        precis = round(abs(k_map[j] - k_real[i][j]), 4)
        print(precis, end=' ')
    print()
