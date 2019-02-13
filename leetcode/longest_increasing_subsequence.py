def binary_search(l, x, l_len):
    s = 0
    e = l_len - 1
    if x <= l[0]: return -1
    if x > l[l_len - 1]: return l_len-1
    while(e - s > 1):
        m = (e + s) // 2
        if l[m] < x:
            s = m
        elif l[m] >= x:
            e = m
    return s
        

class Solution:
    def lengthOfLIS(self, nums):
        nums_len = len(nums)
        if nums_len == 0: return 0
        f = [0 for i in range(nums_len)]
        f[0] = nums[0]
        f_len = 1
        for i in range(1, nums_len):
            x = nums[i]
            largest_smaller = binary_search(f, x, f_len)
            if largest_smaller == f_len -1:
                f[f_len] = x
                f_len += 1
            else:
                f[largest_smaller+1] = x
        return f_len
