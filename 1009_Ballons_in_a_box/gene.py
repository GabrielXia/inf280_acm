# python gene.py > input

import numpy as np

for i in range(1000):
    n = np.random.choice([1,2,3,4,5,6], 1)[0]
    print(n)
    s = np.random.choice(10, 3)
    print(str(s[0]) + ' ' + str(s[1]) + ' ' + str(s[2]))
    e = np.random.choice(10, 3)
    print(str(e[0]) + ' ' + str(e[1]) + ' ' + str(e[2]))
    for j in range(n):
        a = np.random.choice(10, 3)
        print(str(a[0]) + ' ' + str(a[1]) + ' ' + str(a[2]))
print('0')
