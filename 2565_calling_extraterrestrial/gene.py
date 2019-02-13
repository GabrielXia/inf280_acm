import numpy as np

for i in range(10000):
    a = np.random.choice(1000, 1)[0]
    b = np.random.choice(1000, 1)[0]
    if (b < a or a == 0): continue
    print('99999' + ' ' + str(a) + ' ' + str(b))
print('0 0 0')
