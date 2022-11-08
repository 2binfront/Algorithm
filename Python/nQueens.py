# N皇后，每个棋子同行同列同斜线仅一个
# 回溯宽度为每行宽度，回溯深度为总行数
# leetcode 51

from typing import List


class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:

        tmp = [["."] * n for _ in range(n)]
        ans = []

        def isValid(i, j):
            for rangeNum in range(i):
                # 判断每列往上有无Q
                if tmp[rangeNum][j] == "Q":
                    return False

            # 只需判断左上和右上有无Q
            row = i - 1
            col = j - 1
            while row >= 0 and col >= 0:
                if tmp[row][col] == "Q":
                    return False
                row -= 1
                col -= 1
            row = i - 1
            col = j + 1
            while row >= 0 and col < n:
                if tmp[row][col] == "Q":
                    return False
                row -= 1
                col += 1
            return True

        def dfs(index=0):
            if index == n:
                tmpdfs = []
                for row in range(n):
                    tmpstr = "".join(tmp[row])
                    tmpdfs.append(tmpstr)
                ans.append(tmpdfs)

            for col in range(n):
                if isValid(index, col):
                    tmp[index][col] = "Q"
                    dfs(index + 1)
                    tmp[index][col] = "."

        dfs()
        return ans


if __name__ == "__main__":
    sol = Solution()
    n1 = 4
    print(sol.solveNQueens(n1))
