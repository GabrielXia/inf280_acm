class Solution:
    def maxCoins(self, nums):
        length = len(nums)
        news = [nums[i] for i in range(length)]
        news.insert(0, 1)
        news.append(1)
        news_len = length + 2
        f = [[0 for i in range(length+2)] for j in range(length+2)]
        # init 
        for i in range(length):
            f[i][i+2] = news[i] * news[i+1] * news[i+2]
        for i in range(3, news_len):
            for s in range(news_len - i):
                e = s + i
                for last in range(s+1, e):
                    f[s][e] = max(f[s][e], f[s][last] + f[last][e] + news[s] * news[last] * news[e])
        #import pdb; pdb.set_trace()
        return f[0][news_len-1]