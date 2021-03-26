import numpy as np
import random
print("18 Варинат")
print("\nZ1a 6")
arr = np.array([0, 0, 1, 5, 0, 1])
count = 0
print("Индексы ненулевых элементов массива:", end=' ')
for i in range(arr.size):
    if arr[i] != 0:
        print(i, end=' ')
print("\n\nZ1b 11")
n = 5
m = 5
b = np.zeros((n, m), dtype=int)
print("Трёхдиагональная матрица из 1 на главной диагонали, 2 над главной диагональю и 3 под ней:")
if n > m:
    for i in range(m + 1):
        for j in range(m):
            if i == j:
                b[i][j] = 1
                if j < m - 1:
                    b[i][j + 1] = 2
                    b[i + 1][j] = 3
    b[m][m - 1] = 3
    for i in range(len(b)):
        for j in range(len(b[i])):
            print(b[i][j], end='\t')
        print()
elif n < m:
    for i in range(n):
        for j in range(n + 1):
            if i == j:
                b[i][j] = 1
                if j < n - 1:
                    b[i][j + 1] = 2
                    b[i + 1][j] = 3
    b[n - 1][n] = 2
    for i in range(len(b)):
        for j in range(len(b[i])):
            print(b[i][j], end='\t')
        print()
else:
    for i in range(n):
        for j in range(m):
            if i == j:
                b[i][j] = 1
                if j < n - 1:
                    b[i][j + 1] = 2
                    b[i + 1][j] = 3
    for i in range(len(b)):
        for j in range(len(b[i])):
            print(b[i][j], end='\t')
        print()
print("\nZ2 3")
A = np.zeros((5, 5), dtype=int)
print("Исходный случайный массив A 5x5:")
for i in range(len(A)):
    for j in range(len(A[j])):
        A[i][j] = random.randint(-10, 10)
        print(A[i][j], '  ', end='\t')
    print()
print()
A *= 2
print("Массив A со всеми элементами перемноженными на 2:")
for i in range(len(A)):
    for j in range(len(A[j])):
        print(A[i][j], '  ', end='\t')
    print()
