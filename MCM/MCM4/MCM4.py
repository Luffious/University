from math import exp


def to_fixed(num, digits=0):
    return f"{num:.{digits}f}"


def f(x):
    a, b, c, d = 1.49, 4.04, 2.67, 0.12
    return a * exp(-d * pow((x - c), 2)) + b


def method_right_rectangle(n):
    i, x1, x2, dig = 0, -0.7, 4.7, 5
    h = (x2 - x1) / n
    s = 0
    for i in range(n):
        s += h * f((x1 + (i * h)) + h)
    print(s)


def method_middle_rectangle(n):
    i, x1, x2, dig = 0, -0.7, 4.7, 5
    h = (x2 - x1) / n
    s = 0
    for i in range(n):
        s += h * f((x1 + (i * h)) + h / 2)
    print(s)


def method_trapeze(n):
    i, x1, x2, dig = 0, -0.7, 4.7, 5
    h = (x2 - x1) / n
    s = 0
    for i in range(n):
        s += (f(x1 + (i * h)) + f((x1 + (i * h)) + h)) * h / 2
    print(s)


def method_parabola(n):
    i, x1, x2, dig = 0, -0.7, 4.7, 5
    h = (x2 - x1) / n
    s = 0
    for i in range(n):
        s += (f(x1 + (i * h)) + 4 * f((x1 + (i * h)) + h / 2) + f((x1 + (i * h)) + h)) * h / 6
    print(s)


def method_kotes(n):
    i, j, x1, x2, dig, s1 = 0, 0, -0.7, 4.7, 5, 0
    k = [19, 75, 50, 50, 75, 19]
    m = len(k)
    h = (x2 - x1) / n
    s, s0 = [0] * n, [0] * 6
    for i in range(m):
        for j in range(n):
            s[j] = f((x1 + (j * h)) + (i * h) / (m - 1))
        s0[i] = sum(s)
    for i in range(m):
        s1 += s0[i] * k[i]
    s1 /= sum(k) * 1 / h
    print(s1)


n_global = 20
print("Для метода правых прямоугольников значение интеграла равно:", end=' ')
method_right_rectangle(n_global)
print("Для метода средних прямоугольников значение интеграла равно:", end=' ')
method_middle_rectangle(n_global)
print("Для метода трапеций значение интеграла равно:", end=' ')
method_trapeze(n_global)
print("Для метода парабол значение интеграла равно:", end=' ')
method_parabola(n_global)
print("Для метода Котеса 5-го порядка значение интеграла равно:", end=' ')
method_kotes(n_global)
for z in range(100, 251, 50):
    print("Для метода парабол значение интеграла равно:", end=' ')
    method_parabola(z)
