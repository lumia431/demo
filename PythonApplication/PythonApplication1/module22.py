class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        v = set()
        n = len(s)
        rk,ans = -1,0
        for i in range(n):
            if i != 0:
                v.remove(s[i-1])
            while rk + 1 < n and 

