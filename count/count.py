import numpy as np

li = [0 for i in range(10000)]
li[0] = 1
for i in range(1, 10000):
    li[i] = i * li[i-1]

def fact(n):
    return li[n]

def zuhe(a, b):
    up = fact(a)
    down = fact(a) * fact(a-b)
    return up // down

T = input()
mod = 10**9 + 7
for t in range(T):
    N, M = raw_input().split()
    N = int(N)
    M = int(M)
    old_couple = fact(2*(N - M))

    # init
    f = np.zeros((M+1, M+1), dtype=np.int64)
    f[0,0] = old_couple % mod
    f[1, 0] = old_couple * zuhe(2* (N -M) +1, 2)
    f[1, 1] = old_couple * zuhe(2*(N-M) +1, 1)
    #f[1, 0] = 1 * 
    for m in range(2, M + 1):
        for j in range(m+1):
            for k in [1,2]:
                for l in range(1,k +1):
                    f[m, j - l + 2 - k] =  f[m, j - l + 2 - k] + f[m - 1, j] * zuhe(1, k - 1) * zuhe(j, l) * zuhe(2 * (m-1) + 1 -j, k - l) % mod
    
    out = f[M, 0] * (2 ** (M)) % mod
    print('Case #' + str(t+1) + ': ' + str(out))