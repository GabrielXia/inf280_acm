class Solution:
    def minCut(self, s):
        s_len = len(s)
        f = [s_len for i in range(s_len)]
        f[0] = 0
        palindrome = [[False for i in range(s_len)] for j in range(s_len)]
        for i in range(s_len):
            for j in range(i+1):
                if (s[i] == s[j] and (i-j<2 or palindrome[j+1][i-1])):
                    palindrome[j][i] = True
                    if j > 0:
                        m = min(f[i], f[j-1] + 1)
                    else:
                        m = min(f[i], 0)
                    f[i] = m
        #import pdb; pdb.set_trace()
        return f[s_len-1]