# Z2
print("2 задание")
print("Введите натуральное число n")
n = int(input())
print("И целый показатель степени m для этого числа")
m = int(input())
while m <= 0:
    m = int(input())
k = 1
print("Степени натуральных чисел, которые меньше числа", n)
while pow(k, m) < n:
    print(k, "в степени", m, "=", pow(k, m))
    k = k + 1
# Z3
print("\n3 задание")
print("Введите целый x")
x = int(input())
while x == 0:
    x = int(input())
print("И целый y")
y = int(input())
while y == 0:
    y = int(input())
if x > 0:
    if y > 0:
        print("При x =", x, "и y =", y, "график будет лежать в 1 четверти")
    else:
        print("При x =", x, "и y =", y, "график будет лежать в 4 четверти")
if x < 0:
    if y > 0:
        print("При x =", x, "и y =", y, "график будет лежать в 2 четверти")
    else:
        print("При x =", x, "и y =", y, "график будет лежать в 3 четверти")
# Z4
print("\n4 задание")
print("Введите переменную i в диапазоне от 0 до 500")
i = int(input())
while i > 500 or i < 0:
    i = int(input())
step = 1
while i < 500:
    if i % 30 == 0:
        print("i достигло значения, кратного 30:", i)
        break
    elif i % 100 == 0:
        print("i достигло значения, кратного 100:", i)
        break
    i += step
if i == 500:
    print("Done")
