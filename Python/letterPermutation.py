'''
leetcode 784
给定一个字符串 s ，通过将字符串 s 中的每个字母转变大小写，我们可以获得一个新的字符串。
返回 所有可能得到的字符串集合 。以 任意顺序 返回输出。
'''


class Solution:
    def letterCasePermutation(self, s) :
        res=[]
        t=list(s)
        def dfs(index=0):
            if index==len(s):
                res.append(''.join(t))
                return
            dfs(index+1)
            if t[index].isalpha():
                t[index]= t[index].upper() if t[index]==t[index].lower() else t[index].lower()
                dfs(index+1)
        
        dfs()
        return res

if __name__=='__main__':
    s1=Solution()
    case1='1z2b'
    case2 = '3z4'
    print(s1.letterCasePermutation(case1))
    print(s1.letterCasePermutation(case2))
    