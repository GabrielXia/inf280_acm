def radix_sort(nums):
    res = nums
    for i in range(31):
        q0 = list()
        q1 = list()
        for j in res:
            bin_j = bin(j)[2:]
            if i >= len(bin_j) or bin_j[-(i+1)] == '0':
                q0.append(j)
            elif bin_j[-(i+1)] == '1':
                q1.append(j)
        res = []
        for q in q0:
            res.append(q)
        for q in q1:
            res.append(q)
        #import pdb; pdb.set_trace()
    return res


class Solution:
    def maximumGap(self, nums):
        """
        :type nums: List[int], int 32 bit 
        :rtype: int
        """
        if len(nums) < 2:
            return 0
        else:
            res = radix_sort(nums)
            maxv = 0
            for i in range(len(res) -1):
                if (res[i + 1] - res[i]) > maxv:
                    maxv = res[i + 1] - res[i]
        return maxv
