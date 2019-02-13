class Solution:
    def jump(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        l = len(nums)
        if l <= 1: return 0
        current_e = 0
        current_level = 0
        next_s = current_e + 1
        next_e = next_s
        for i in range(l):
            step_size = nums[i]
            next_e = max(next_e, i + step_size)
            if next_e >= l - 1:
                return current_level + 1
            if i == current_e:
                current_level += 1
                current_e = next_e
                next_s = next_e + 1
                next_e = next_s