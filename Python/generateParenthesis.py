# 数字 n 代表生成括号的对数，
# 请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
# leetcode 22 括号生成
#

from typing import List


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        ans = []
        tmp = []

        def dfs(index=0, leftCount=0, rightCount=0):
            if index == 2 * n:
                ans.append("".join(tmp))
                return
            if leftCount == rightCount:
                tmp.append("(")
                leftCount += 1
                dfs(index + 1, leftCount, rightCount)
                tmp.pop()
                leftCount -= 1
                return
            elif leftCount > rightCount and leftCount < n:
                tmp.append("(")
                leftCount += 1
                dfs(index + 1, leftCount, rightCount)
                tmp.pop()
                leftCount -= 1

                tmp.append(")")
                rightCount += 1
                dfs(index + 1, leftCount, rightCount)
                tmp.pop()
                rightCount -= 1

                return

            elif leftCount == n:
                tmp.append(")")
                rightCount += 1
                dfs(index + 1, leftCount, rightCount)
                tmp.pop()
                rightCount -= 1

        dfs()
        return ans


if __name__ == "__main__":
    solution1 = Solution()
    n1 = 3
    print(solution1.generateParenthesis(n1))
