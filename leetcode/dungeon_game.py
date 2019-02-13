class Solution:
    def calculateMinimumHP(self, dungeon):
        m = len(dungeon)
        n = len(dungeon[0])
        f = [[0 for i in range(n)] for j in range(m)]
        f[m-1][n-1] = max(0, - dungeon[m-1][n-1])
        for i in range(m-1, -1, -1):
            for j in range(n-1, -1, -1):
                if i == m - 1 and j == n - 1: pass
                elif i == m - 1:
                    f[i][j] = max(f[i][j+1] - dungeon[i][j], 0)
                elif j == n - 1:
                    f[i][j] = max(f[i+1][j] - dungeon[i][j], 0)
                else:
                    f1 = max(f[i+1][j] - dungeon[i][j], 0)
                    f2 = max(f[i][j+1] - dungeon[i][j], 0)
                    f[i][j] = min(f1, f2)
        # import pdb; pdb.set_trace()
        return f[0][0]