class Solution:
    def isMatch(self, s, p):
        s_len = len(s)
        p_len = len(p)
        f = [[False for i in range(s_len)] for j in range(p_len)]
        if s_len == 0 and p_len == 0:
            return True
        if s_len == 0:
            res = True
            for i in range(p_len):
                if p[i] != '*': res = False
            return res
        if p_len == 0:
            return False
        f[0][0] = True if (p[0] == s[0] or p[0] == '*' or p[0] == '?') else False
        # colone 1
        once = True if p[0] != '*' else False
        for i in range(1, p_len):
            if p[i] == '*':
                f[i][0] = f[i-1][0]
            elif p[i] == '?':
                if not once:
                    f[i][0] = f[i-1][0]
                    once = True
            else:
                if p[i] == s[0]:
                    if not once:
                        f[i][0] = f[i-1][0]
                        once = True
                else:
                    f[i][0] = False
                    once = True
        # row 1
        for i in range(1, s_len):
            if p[0] == '*':
                f[0][i] = True
            else:
                f[0][i] = False
        for i in range(1, s_len):
            for j in range(1, p_len):
                if p[j] == '*':
                    f[j][i] = (f[j][i-1] | f[j-1][i-1] | f[j-1][i])
                elif (p[j] == '?') or (p[j] == s[i]):
                    f[j][i] = f[j-1][i-1]
                else:
                    f[j][i] = False
        return f[p_len-1][s_len-1]
        