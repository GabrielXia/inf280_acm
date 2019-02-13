class Solution:
    def minDistance(self, word1, word2):
        word1_len = len(word1)
        word2_len = len(word2)
        f = list()
        f.append(list(range(word1_len + 1)))
        for i in range(1, word2_len+1):
            fi = list()
            fi.append(i)
            for j in range(1, word1_len+1):
                if word1[j - 1] == word2[i - 1]:
                    small = min(f[i-1][j-1], f[i-1][j] + 1, fi[j-1] +1)
                    fi.append(small)
                else:
                    small = min(f[i-1][j-1] + 1, f[i-1][j] + 1, fi[j-1] + 1)
                    fi.append(small)
            f.append(fi)
        return f[word2_len][word1_len]




        