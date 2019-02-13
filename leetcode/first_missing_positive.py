def swap(nums, i, j):
    tmp = nums[i]
    nums[i] = nums[j]
    nums[j] = tmp


class Solution:
    def firstMissingPositive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        l = len(nums)
        for i in range(l):
            if nums[i] <=0 or nums[i] > l:
                nums[i] = -1
        # swap
        for i in range(l):
            while not (nums[i] == i + 1 or nums[i] == -1):
                if nums[nums[i] - 1] == nums[i]:
                    nums[i] = -1
                else:
                    swap(nums, i, nums[i]-1)
        
        for i in range(l):
            if nums[i] == -1:
                return i + 1
        return l + 1