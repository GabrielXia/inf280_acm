class Solution:
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        l = len(s)
        f = list()
        f.append(0)
        for i in range(1, l):
            if s[i] == '(':
                f.append(0)
            elif s[i] == ')':
                longest = 0
                if f[i-1] == 0:
                    if s[i-1] == ')': 
                        f.append(0)
                    elif s[i-1] == '(':
                        longest += 2
                        before = f[i-2] if i > 2 else 0
                        longest += before
                        f.append(longest)
                else:
                    tmp = i - 1
                    while f[tmp] != 0 and tmp > 0:
                        longest += f[tmp]
                        tmp -= f[tmp]
                    if tmp < 0:
                        f.append(0)
                    elif s[tmp] == '(':
                        longest += 2
                        longest += (f[tmp-1] if tmp > 0 else 0)
                        f.append(longest)
                    elif s[tmp] == ')':
                        f.append(0)
        return max(f)