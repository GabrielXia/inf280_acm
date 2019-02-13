def search_matrix(matrix, sm, em, sn, en, target):
    upleft = matrix[sm][sn]
    downright = matrix[em][en]
    if target < upleft or target > downright:
        return False
    else:
        if target == upleft or target == downright:
            return True
        else:
            #import pdb; pdb.set_trace()
            median_m = (sm + em) // 2
            median_n = (sn + en) // 2
            a = search_matrix(matrix, sm, median_m, sn, median_n, target)
            b, c, d = False, False, False
            if em > sm:
                b = search_matrix(matrix, median_m + 1, em, sn, median_n, target)
            if en > sn:
                c = search_matrix(matrix, sm, em, median_n + 1, en, target)
            if em > sm and en > sn:
                d = search_matrix(matrix, median_m + 1, em, median_n + 1, en, target)
            return (a | b | c | d )

class Solution:
    def searchMatrix(self, matrix, target):
        """
        :type matrix: List[List[int]]
        :type target: int
        :rtype: bool
        """
        if len(matrix) == 0: return False
        if len(matrix[0]) == 0: return False
        m = len(matrix)
        n = len(matrix[0])
        return search_matrix(matrix, 0, m -1, 0, n -1, target)
        