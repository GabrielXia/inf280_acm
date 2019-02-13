class Solution:
    def numDistinct(self, s, t):
        s_len = len(s)
        t_len = len(t)
        f = [[0 for i in range(s_len)] for j in range(t_len)]
        # init
        t0 = t[0]
        for i in range(s_len):
            if t0 == s[i]:
                f[0][i] = 1
        
        # n -> n + 1
        for i in range(1, t_len):
            index = 0
            sum = 0
            for j in range(s_len):
                if s[j] == t[i]:
                    for k in range(index, j):
                        sum += f[i-1][k]
                    index = j
                    f[i][j] = sum
        #import pdb; pdb.set_trace()
        sum = 0
        for i in range(s_len):
            sum += f[t_len-1][i]
        return sum