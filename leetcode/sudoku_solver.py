def accept(borad, i, k):
    x, y = i // 9, i % 9
    # check line
    for j in range(9):
        if str(k) == borad[x][j]: return False
        if str(k) == borad[j][y]: return False
        if str(k) == borad[3*(x//3) + j//3][3*(y//3) + j%3]: return False
    return True
        
    
def solve(borad, i):
    if i > 80: return True  
    x, y = i // 9, i % 9
    if borad[x][y] != '.': return solve(borad, i + 1)
    # seek for potential number
    for j in range(1, 10):
        if accept(borad, i, j):
            borad[x][y] = str(j)
            if solve(borad, i+1):
                return True
            borad[x][y] = '.'
    return False

 
class Solution:
    def solveSudoku(self, board):
        """
        Do not return anything, modify board in-place instead.
        """
        solve(board, 0)    
        return 