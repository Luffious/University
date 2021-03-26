# Z2
import random
random.seed()
A = [random.randint(0, 9)] * 10
for i in range(10):
    A[i] = [random.randint(0, 9), random.randint(0, 9), random.randint(0, 9)]
for i in range(0, 10, 2):
    b = (random.uniform(0, 9), random.uniform(0, 9), random.uniform(0, 9))
    b_list = list(b)
    var = A[i] + b_list
    A[i] = var
# a
print(A, '\n')
# b
i = 0
while i <= A.__len__() - 1:
    temp = A[i + 1]
    A[i + 1] = A[i]
    A[i] = temp
    i += 2
print(A, '\n')
# c
A.clear()
print(A, '\n')
# Z3
A = ("Tom", "picture", 22, "sunny", 365, "water")
B = ("milk", "juice", "orange", "dinner", "breakfast", "water", 365)
# a
print(A + B, '\n')
# b
print(A.__len__(), B.__len__(), '\n')
# c
C = 22 in A
D = 22 in B
if C is True and D is True:
    print('22 Есть и в A и в B')
elif C is True and D is False:
    print('22 Есть только в A')
elif C is False and D is True:
    print('22 Есть только в B')
else:
    print('22 нет ни в A, ни в B')
print('\n')
# d
C = list(A)
D = list(B)
C[1] = D
print(tuple(C), '\n')
# Z4
A = [('a', 1), ('b', 2), ('c', 3), ('d', 4), ('e', 5), ('f', 6)]
B = dict(A)
print(B, '\n')
# a
print(B.keys(), '\n')
# b
print([B.get('d')], '\n')
# c
print(B.items(), '\n')
# d
print([B.get('h')], '\n')
# e
B.clear()
print(B, '\n')
