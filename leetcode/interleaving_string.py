class Solution:
    def isInterleave(self, s1, s2, s3):
        s1_len = len(s1)
        s2_len = len(s2)
        s3_len = len(s3)
        if s1_len + s2_len != s3_len:
            return False
        if s3_len == 0:
            return True
        # init
        f = [[False for j in range(s2_len + 1)] for i in range(s1_len + 1)]
        if s1_len != 0 and s3[0] == s1[0]:
            f[1][0] = True
        if s2_len != 0 and s3[0] == s2[0]:
            f[0][1] = True
        
        for i in range(s1_len + 1):
            for j in range(s2_len + 1):
                if i + j > 1 and i + j -1 < s3_len:
                    if i > 0:
                        f[i][j] |= (f[i-1][j] & (s1[i-1] == s3[i+j-1]))
                    if j > 0:
                        f[i][j] |= (f[i][j-1] & (s2[j-1] == s3[i+j-1]))

        return f[s1_len][s2_len]

