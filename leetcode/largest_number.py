class Solution: 

    @staticmethod
    def less_than(x, y):
        x, y = str(x), str(y)
        if len(x) ==  0 or len(y) == 0:
            return False
        for i, xi in enumerate(x):
            if i >= len(y):
                return Solution.less_than(x[i:], x[:i])
            yi = y[i]
            if xi == yi:
                if i == len(x) -1:
                    return not Solution.less_than(y[i+1:], x[:i+1])
                else: continue
            else:
                return (xi < yi)
    
    @staticmethod
    def swap(list0, a, b):
        tmp = list0[a]
        list0[a] = list0[b]
        list0[b] = tmp

    @staticmethod
    def partition(list0, l, r, pivot_index):
        pivot = list0[pivot_index]
        Solution.swap(list0, r, pivot_index)
        current_pivot_index = l
        for i in range(l, r):
            if Solution.less_than(list0[i], pivot):
                Solution.swap(list0, i, current_pivot_index)
                current_pivot_index += 1
        Solution.swap(list0, current_pivot_index, r)
        return current_pivot_index
    
    @staticmethod
    def quicksort(list0, l, r):
        if l < r:
            pivot_index = l
            pivot = Solution.partition(list0, l, r, pivot_index)
            Solution.quicksort(list0, l, pivot-1)
            Solution.quicksort(list0, pivot+1, r)

    # @staticmethod
    # def sort(list0):
    #     res = []
    #     for i, v1 in enumerate(list0):
    #         if i == 0:
    #             res.append(v1)
    #         else:
    #             for j, vj in enumerate(res):
    #                 import pdb; pdb.set_trace()
    #                 if Solution.less_than(v1,vj):
    #                     res.insert(j, v1)
    #                     break
    #                 elif j == len(res) -1:
    #                     res.append(v1)
    #     return res

    @staticmethod
    def bubble_sort(list0):
        n = len(list0)
        for i in range(n):
            for j in range(n-i-1):
                if Solution.less_than(list0[j+1], list0[j]):
                    Solution.swap(list0, j,  j+1)

    def largestNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: str
        """
        n = len(nums)
        Solution.quicksort(nums, 0, n-1)
        nums = reversed(nums)
        res = ''
        for i in nums:
            if len(res) == 0 and int(i) == 0:
                continue
            res += str(i)
        if len(res) == 0: res='0'
        return res  